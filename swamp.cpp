#include "swamp.h"
#include "server/connection.h"
#include "character/player.h"
#include "utils/text_logger.h"

#include <thread>
#include <chrono>

namespace swamp {

//------------------------------------------------------------------------------
Swamp::Swamp()
	: m_server() {

	TextLogger::getInstance()->write(LogLevel::LOG_INFO, __PRETTY_FUNCTION__);
	m_server.registerAcceptListener(this);
}

//------------------------------------------------------------------------------
Swamp::~Swamp() {
	m_server.unregisterAcceptListener(this);
}

//------------------------------------------------------------------------------
int Swamp::run() {
	std::thread server_thread(&swamp::Server::run, &m_server);
	bool shutdown = false;

	while (!shutdown) {

		//updateNonPlayerCharacters();
		updatePlayers();

		std::this_thread::sleep_for(std::chrono::microseconds(Swamp::SWAMP_TICK_IN_US));
	}

	server_thread.join();
	return 0;
}

//------------------------------------------------------------------------------
bool Swamp::notify(Connection* connection) {
	bool result = false;

	TextLogger::getInstance()->write(LogLevel::LOG_INFO, __PRETTY_FUNCTION__);

// TODO: Add some connection validation
	if (connection != nullptr) {
		m_mutex.lock();
		Player*& player = m_players.insert(std::make_pair(connection, nullptr)).first->second;
		if (player == nullptr) {
			player = new Player;
			m_server.registerReadListener(player);
			player->setConnection(connection);
		}
		m_mutex.unlock();
	}

	return result;
}

//------------------------------------------------------------------------------
int Swamp::nanny(Player* player) {
	int result = -1;

	std::string cmd;
	player->read(cmd);

	if (player->isConnected()) {
		switch (player->getConnectionState()) {
			//------------------------------------------------------------------------
			case Player::ConnectionState::CON_STATE_LOGIN: {
				if (cmd == "admin") {
					player->write("Wohoo, admin on the board!\n");
					player->setConnectionState(Player::ConnectionState::CON_STATE_PASSWORD);
					player->write("Password: ");
				}
				break;
			}

			//------------------------------------------------------------------------
			case Player::ConnectionState::CON_STATE_PASSWORD: {
				if (cmd == "admin") {
					player->write("Welcome master!\n");
					player->setConnectionState(Player::ConnectionState::CON_STATE_INGAME);
				}
				break;
			}

			//------------------------------------------------------------------------
			default: {
				player->write("User name: ");
				player->setConnectionState(Player::ConnectionState::CON_STATE_LOGIN);
				break;
			}
		}
	}
	else {
		printf("%s:%u (lost link)\n", __PRETTY_FUNCTION__, __LINE__);
	}

	return result;
}

//------------------------------------------------------------------------------
void Swamp::updatePlayers() {
	// Players
	m_mutex.lock();
	for (auto& p : m_players) {
		if (p.second != nullptr) {
			if (p.second->isConnected()) {
				if (p.second->isInGame()) {

					p.second->update(0.0f);
				}
				else {
					nanny(p.second);
				}
			}
		}
	}
	m_mutex.unlock();
}

} /* namespace swamp */

