/** \file connection.h */
#ifndef SWAMP_CONNECTION_H
#define SWAMP_CONNECTION_H

#include <cstddef>

/**\addtogroup server */
/** @{ */

/**
 * \namespace swamp
 */
namespace swamp {

/**
 * \struct connection
 * \ingroup server
 */
struct Connection {
	Connection(int fd);
	virtual ~Connection();

	int open();
	int close();

	int write(const char* /*buffer*/, size_t /*len*/);
	int read(char* /*buffer*/, size_t /*max_len*/);

	int getDescriptor() const;

	private:
		int m_in_fd;
		int m_out_fd;
		unsigned int m_port;
};

}; /* namespace swamp */

#endif /* SWAMP_CONNECTION_H */

/** @} */
