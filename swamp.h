#ifndef SWAMP_SWAMP_H
#define SWAMP_SWAMP_H

#include <unordered_map>

#include "server/server.h"
#include "server/server_listeners.h"

/**
 * \namespace swamp
 */
namespace swamp {

struct Connection;
struct Player;

/**
 * \struct Swamp
 */
struct Swamp : public AcceptListener {
	Swamp();
	virtual ~Swamp();

	Swamp(const Swamp&) = delete;
	Swamp& operator=(const Swamp&) = delete;

	int run();

	int nanny(Player* player);

	private:
		bool notify(Connection* connection);
		void updatePlayers();

	private:
		enum {
			SWAMP_TICK_IN_US = 1000U /**<  TIck value in microseconds */
		};

		typedef std::unordered_map<Connection*, Player*> players_t;

		players_t m_players;
		Server m_server;
		std::mutex m_mutex;
};

} /* namespace swamp */

#endif /* SWAMP_SWAMP_H */
