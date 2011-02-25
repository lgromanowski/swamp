/** \file character/player.h */
#ifndef SWAMP_PLAYER_H
#define SWAMP_PLAYER_H

/**\addtogroup character */
/** @{ */

/**
 * \namespace swamp
 */
namespace swamp
{

/**
 * \class Player
 * \ingroup character
 */
class Player : public Character
{
  public:
    Player();
    virtual ~Player();

    /**
     * \brief Executes command
     *
     * \param [in] cmd
     *
     * \return int
     */
    int doCommand(Command& cmd);
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

