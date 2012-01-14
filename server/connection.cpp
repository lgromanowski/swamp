#include "connection.h"

#include <unistd.h>
#include <fcntl.h>
#include <cstdio>

namespace swamp {

//------------------------------------------------------------------------------
Connection::Connection(int fd)
	: m_in_fd(fd)
	, m_out_fd(-1) {
}

//------------------------------------------------------------------------------
Connection::~Connection() {
	close();
}

//------------------------------------------------------------------------------
int Connection::open() {
	int result = fcntl(m_in_fd, F_GETFL, 0);
	if (result >= 0) {
		result = fcntl(m_in_fd, F_SETFL, result | O_NONBLOCK);
	}

	if (result >= 0) {
		m_out_fd = fcntl(m_in_fd, F_DUPFD, 0);
	}
	return result;
}

//------------------------------------------------------------------------------
int Connection::close() {
	printf("Closed connection on descriptors %d/%d\n", m_in_fd, m_out_fd);

	if (m_in_fd != -1) {
		::close(m_in_fd);
		m_in_fd = 1;
	}

	if (m_out_fd != -1) {
		::close(m_out_fd);
		m_out_fd = 1;
	}

	return 0;
}

//------------------------------------------------------------------------------
int Connection::write(const char* buffer, size_t len) {
		printf("%s:%u\n", __PRETTY_FUNCTION__, __LINE__);

	return ::write(m_out_fd, buffer, len);
}

//------------------------------------------------------------------------------
int Connection::read(char* buffer, size_t max_len) {
		printf("%s:%u\n", __PRETTY_FUNCTION__, __LINE__);

	return ::read(m_in_fd, buffer, max_len);
}


} /* namespace swamp */
