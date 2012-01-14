#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

#include <algorithm>

#include "connection.h"
#include "server_listeners.h"
#include "utils/text_logger.h"


/**
 * \namespace swamp
 */
namespace swamp {

//------------------------------------------------------------------------------
Server::Server()
	: m_socket(-1)
	, m_epoll_fd(-1)
	, m_mutex() {
}

//------------------------------------------------------------------------------
Server::~Server() {
	shutdown();
}

//------------------------------------------------------------------------------
void Server::run(/* const char* port*/) {
	const char* port = "6666";

	bind(port);
	listen();

	m_epoll_fd = epoll_create1(0);
	if (m_epoll_fd >= 0) {
		struct epoll_event event{EPOLLIN | EPOLLET, {reinterpret_cast<void*>(m_socket)}};

		int ret = epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_socket, &event);
		if (ret >= 0) {
			struct epoll_event* events = static_cast<epoll_event*>(calloc(MAX_EVENTS, sizeof(event)));

			while (true) {
				int available_events = epoll_wait(m_epoll_fd, events, MAX_EVENTS, 0 /* -1 */);
				for (int i = 0; i < available_events; i++) {
					if ((events[i].events & EPOLLERR)
						|| (events[i].events & EPOLLHUP)
						|| (!(events[i].events & EPOLLIN))) {

						::close(events[i].data.fd);
						continue;
					}
					else if (m_socket == events[i].data.fd) {
						accept();
					}
					else if (events[i].data.ptr != nullptr) {
						std::lock_guard<std::mutex> lock(m_read_mutex);

						Connection* connection = static_cast<Connection*>(events[i].data.ptr);
						for (auto& listener : m_read_listeners) {
							listener->notify(connection);
						}
					}
				}
			}

			free(events);
		}
	}
}

//------------------------------------------------------------------------------
int Server::accept() {
	struct sockaddr in_addr;
	memset(&in_addr, 0, sizeof(in_addr));

	int result = 0;

	while (1) {
		socklen_t in_len = sizeof(in_addr);
		int infd = ::accept(m_socket, &in_addr, &in_len);
		if (infd >= 0) {

			Connection* connection = new Connection(infd);
			result = connection->open();
			if (result >= 0) {
				char hbuf[NI_MAXHOST] = {0};
				char sbuf[NI_MAXSERV] = {0};

				result = getnameinfo(&in_addr, in_len, hbuf, sizeof(hbuf),
					sbuf, sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV);

				if (result == 0) {
					TextLogger::getInstance()->write(LogLevel::LOG_INFO, "Accepted connection on descriptor %d (host=%s, port=%s)\n", infd, hbuf, sbuf);
					printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", infd, hbuf, sbuf);
				}

				watch(connection, infd);

				{
					std::lock_guard<std::mutex> lock(m_accept_mutex);

					for (auto& listener : m_accept_listeners) {
						if (listener->notify(connection)) {
							break;
						}
					}
				}
			}
			else {
				TextLogger::getInstance()->write(LogLevel::LOG_ERROR, "Failed to open connection (fd: %d)\n", infd);
				delete connection;
			}
		}
		else {
			if ((errno != EAGAIN) && (errno != EWOULDBLOCK)) {
				TextLogger::getInstance()->write(LogLevel::LOG_ERROR, strerror(errno));
			}
			break;
		}
	}
	return result;
}

//------------------------------------------------------------------------------
int Server::watch(Connection* connection, int fd) {
	struct epoll_event event;
	event.data.ptr = connection;
	event.events = EPOLLIN | EPOLLET;
	return epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, fd, &event);
}

//------------------------------------------------------------------------------
int Server::unwatch(int fd) {
	return epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
}

//------------------------------------------------------------------------------
int Server::shutdown() {
	unwatch(m_socket);
	close(m_socket);
	return 0;
}

//------------------------------------------------------------------------------
int Server::bind(const char* port) {

	struct addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
	hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
	hints.ai_flags = AI_PASSIVE;     /* All interfaces */

	struct addrinfo* result = nullptr;

	int ret = getaddrinfo(nullptr, port, &hints, &result);
	if (ret == 0) {
		for (struct addrinfo* rp = result; rp != nullptr; rp = rp->ai_next) {

			m_socket = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
			if (m_socket >= 0) {
				if (::bind(m_socket, rp->ai_addr, rp->ai_addrlen) == 0) {
					break;
				}

				close(m_socket);
				m_socket = -1;
			}
		}

		if (m_socket >= 0) {
			// TODO: Make a proper error codes
			ret = -42;

			int flags = fcntl(m_socket, F_GETFL, 0);
			if (flags >= 0) {
				if (fcntl(m_socket, F_SETFL, flags | O_NONBLOCK) == 0) {
					ret = 0;
				}
			}
		}

		freeaddrinfo(result);
	}

	return ret;
}

//------------------------------------------------------------------------------
int Server::listen() {
	return ::listen(m_socket, SOMAXCONN);
}

//------------------------------------------------------------------------------
int Server::registerAcceptListener(AcceptListener* listener) {
	int result = -1;
	if (listener != nullptr) {
		m_accept_listeners.push_back(listener);
		result = 0;
	}
	return result;
}

//------------------------------------------------------------------------------
int Server::unregisterAcceptListener(AcceptListener* listener) {
	int result = -1;
	if (listener != nullptr) {
		auto element = std::find(m_accept_listeners.begin(), m_accept_listeners.end(), listener);
		if (element != m_accept_listeners.end()) {
			m_accept_listeners.erase(element);
			result = 0;
		}
	}
	return result;
}

//------------------------------------------------------------------------------
int Server::registerReadListener(ReadRequestListener* listener) {
	int result = -1;
	if (listener != nullptr) {
		m_read_listeners.push_back(listener);
		result = 0;
	}
	return result;
}

//------------------------------------------------------------------------------
int Server::unregisterReadListener(ReadRequestListener* listener) {
	int result = -1;
	if (listener != nullptr) {
		auto element = std::find(m_read_listeners.begin(), m_read_listeners.end(), listener);
		if (element != m_read_listeners.end()) {
			m_read_listeners.erase(element);
			result = 0;
		}
	}
	return result;
}


} /* namespace swamp */
