/** \file server.h */
#ifndef SWAMP_SERVER_H
#define SWAMP_SERVER_H

#include <list>
#include <mutex>

/**\addtogroup server */
/** @{ */

/**
 * \namespace swamp
 */
namespace swamp {


struct Connection;
struct AcceptListener;
struct ReadRequestListener;

/**
 * \struct Server
 * \ingroup server
 */
struct Server {
	Server();
	virtual ~Server();

	/**
	 * Create server socket and start listening loop
	 *
	 * \param [in] port - port number used by server
	 *
	 * \retval   0 - OK
	 * \retval < 0 - ERROR
	 */
	void run(/*const char* port*/);

	int shutdown();

	int registerAcceptListener(AcceptListener* listener);
	int unregisterAcceptListener(AcceptListener* listener);

	int registerReadListener(ReadRequestListener* listener);
	int unregisterReadListener(ReadRequestListener* listener);

	private:
		enum { MAX_EVENTS = 64 };

		int bind(const char* port);
		int listen();
		int accept();
		int watch(Connection* connection, int fd);
		int unwatch(int fd);

	private:
		typedef std::list<Connection*> connections_t;
		typedef std::list<AcceptListener*> accept_listeners_t;
		typedef std::list<ReadRequestListener*> read_listeners_t;

		int m_socket;		/**< Server socket */
		int m_epoll_fd;		/**< epoll file descriptor */
		connections_t m_connections; 	/**< Container which holds all working connections */

		accept_listeners_t m_accept_listeners;
		read_listeners_t m_read_listeners;

		std::mutex m_mutex;
		std::mutex m_accept_mutex;
		std::mutex m_read_mutex;
};

}; /* namespace swamp */

#endif /* SWAMP_SERVER_H */

/** @} */
