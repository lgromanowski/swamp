/** \file character/non_player_character.h */
#ifndef SWAMP_NON_PLAYER_CHARACTER_H
#define SWAMP_NON_PLAYER_CHARACTER_H

/** \addtogroup character */
/** @{ */

/**
 * \namespace swamp
 */
namespace swamp
{

/**
 * \class NonPlayerCharacter
 * \ingroup character
 *
 * \brief NPC class
 */
class NonPlayerCharacter : public Character
{
  public:
    /**
     * \brief Constructor
     */
    NonPlayerCharacter();

    /**
     * \brief Destructor
     */
    virtual ~NonPlayerCharacter();

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
 * \struct non_player_character_info_t
 * \ingroup character
 */
struct non_player_character_info_t
{
  unsigned int index;


};


}; /* namespace swamp */

#endif /* SWAMP_NON_PLAYER_CHARACTER_H */
/** @} */

