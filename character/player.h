/** \file character/player.h */
#ifndef SWAMP_PLAYER_H
#define SWAMP_PLAYER_H

#include "character.h"
#include "server/server_listeners.h"
#include <queue>
#include <vector>

/**\addtogroup character */
/** @{ */

/**
 * \namespace swamp
 */
namespace swamp {

struct Connection;

/**
 * \struct Player
 * \ingroup character
 */
struct Player : public Character, public ReadRequestListener {
	enum class ConnectionState : unsigned int {
		CON_STATE_BEFORE_LOGIN,
		CON_STATE_LOGIN,
		CON_STATE_PASSWORD,
		CON_STATE_INGAME,
		CON_STATE_LOST_LINK
	};

	Player();
	virtual ~Player();

	bool notify(Connection* connection);
	void setConnection(Connection* connection);
	int write(const std::string& text);
	int read(std::string& cmd);

	int update(const float& tick);

	ConnectionState getConnectionState() const;
	void setConnectionState(ConnectionState state);

	bool isInGame() const;
	bool isConnected() const;
	bool isPromptEnabled() const;

	private:
		void displayPrompt();

	private:
		enum { READ_BUF_LEN = 512U };

		Connection* m_connection;
		char m_buf[READ_BUF_LEN];
		std::string m_command;
		std::string m_last_command;
		ConnectionState m_conn_state;

		typedef std::queue<std::string/*, std::vector*/> commands_buffer_t;
		commands_buffer_t m_commands;
		std::string m_prompt;
		bool m_prompt_enabled;
};

/**
 * \struct player_info_t
 * \ingroup character
 */
struct player_info_t
{
};

/**
 * \struct player_data_t
 * \ingroup character
 */
struct player_data_t
{
};

}; /* namespace swamp */

#endif /* SWAMP_PLAYER_H */
/** @} */

