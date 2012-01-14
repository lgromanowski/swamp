#include "player.h"

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

#include "server/connection.h"
#include "utils/string_utils.h"
#include "utils/text_logger.h"

/**\addtogroup character */
/** @{ */

/**
 * \namespace swamp
 */
namespace swamp {

//------------------------------------------------------------------------------
Player::Player()
	: m_connection(nullptr)
	, m_command()
	, m_conn_state(ConnectionState::CON_STATE_BEFORE_LOGIN)
	, m_prompt("0/0hp 0/0mn 0/0mv>")
	, m_prompt_enabled(true) {

}

//------------------------------------------------------------------------------
Player::~Player() {
	delete m_connection;
}

//------------------------------------------------------------------------------
void Player::setConnection(Connection* connection) {
	if ((m_connection != nullptr) && (connection != m_connection)) {
		delete m_connection;
	}

	m_connection = connection;
}

//------------------------------------------------------------------------------
bool Player::notify(Connection* connection) {
	bool result = false;
	if (connection == m_connection) {
		result = true;
		int done = 0;

		while (true) {
			ssize_t count = m_connection->read(m_buf, sizeof(m_buf));
			if (count == -1) {
				/* If errno == EAGAIN, that means we have read all data, otherwise
				it's an error so close connection. */
				if (errno != EAGAIN) {
					TextLogger::getInstance()->write(LogLevel::LOG_ERROR, strerror(errno));
					done = 1;
				}
				break;
			} else if (count == 0) {
				/* End of file. The remote has closed the	connection. */
				done = 1;
				break;
			}
		}

		if (!done) {
			m_command = m_buf;
			trim_whitespaces(m_command);
			m_commands.push(m_command);
		}
		else {
			/* Closing the connection will make epoll remove it
			from the set of descriptors which are monitored. */
			delete m_connection;
			m_conn_state = ConnectionState::CON_STATE_LOST_LINK;
		}
	}

	return result;
}

//------------------------------------------------------------------------------
int Player::write(const std::string& text) {
	return m_connection->write(text.c_str(), text.length());
}

//------------------------------------------------------------------------------
int Player::read(std::string& cmd) {
	int result = -1;

	if (!m_commands.empty()) {
		cmd = m_commands.front();
		m_commands.pop();

// TODO: This should be corrected.
		if (isInGame() && !m_commands.empty()) {
			if (strncmp(m_commands.front().c_str(), "!", sizeof("!") - 1) == 0) {
				m_commands.push(cmd);
				m_commands.pop();
			}
		}

		result = 0;
	}

	return result;
}

//------------------------------------------------------------------------------
int Player::update(const float& /*tick*/) {
	return 0;
}

//------------------------------------------------------------------------------
Player::ConnectionState Player::getConnectionState() const {
	return m_conn_state;
}

//------------------------------------------------------------------------------
void Player::setConnectionState(Player::ConnectionState state) {
	m_conn_state = state;
}

//------------------------------------------------------------------------------
bool Player::isInGame() const {
	return (m_conn_state == ConnectionState::CON_STATE_INGAME);
}

//------------------------------------------------------------------------------
bool Player::isConnected() const {
	return (m_conn_state != ConnectionState::CON_STATE_LOST_LINK);
}

//------------------------------------------------------------------------------
bool Player::isPromptEnabled() const {
	return m_prompt_enabled;
}

//------------------------------------------------------------------------------
void Player::displayPrompt() {
	if (isInGame() && isPromptEnabled()) {
		m_connection->write(m_prompt.c_str(), m_prompt.length());
	}
}

}; /* namespace swamp */

/** @} */

