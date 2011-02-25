/** \file character/character.h */
#ifndef SWAMP_CHARACTER_H
#define SWAMP_CHARACTER_H

/**\addtogroup character */
/** @{ */

/**
 * \namespace swamp
 */
namespace swamp
{

struct Command
{
  const char* m_param_str;
};

/**
 * \struct Language
 */
struct Language
{
  /**
   * \typedef translate_fun_f
   */
  typedef int (Language::translate_fun_f*)(const char* input, char* output);

  unsigned int m_race_id;                   /**< */
};

/**
 * \struct BasicAttributes
 * \ingroup character
 *
 * \brief .
 */
struct BasicAttributes
{
  unsigned int m_hit_points;
  unsigned int m_magick_points; // mana

  unsigned int m_stamina;
  unsigned int m_visdom;
  unsigned int m_charisma;
  unsigned int m_luck;
  unsigned int m_strength;
  unsigned int m_inteligence;
  unsigned int m_speed;
};

/**
 * \struct Level
 * \ingroup character
 *
 * \brief
 *
 * \todo This class sucks, it should be medified
 */
struct Level
{
  unsigned int m_experience_points;
  unsigned int m_level;
};

/**
 * \struct Skill
 * \ingroup character
 */
struct Skill
{
  unsigned int m_skill_id;
};

/**
 * \struct Punishment
 * \ingroup character
 */
struct Punishment
{
  unsigned int m_punishment_id;
  BasicAttributes m_attributes;
};

/**
 * \struct CharacterRace
 * \ingroup character
 *
 * \brief
 */
struct CharacterRace
{
  unsigned int m_race_id;
  unsigned int m_favourite_class;

  BasicAttributes m_race_attributes;
};

/**
 * \struct CharacterClass
 * \ingroup character
 *
 * \brief Contains information about character classes, eg. Monk, Knight, etc.
 */
struct CharacterClass
{
  unsigned int m_class_id;

  BasicAttributes m_class_attributes;
};

typedef std::map<unsigned int /* level */, std::vector<CharacterClass*> >

/**
 * \struct Character
 * \ingroup character
 *
 * \brief Base class for game characters (player, npc).
 */
struct Character
{
  /**
   * \brief character class destructor
   */
  virtual ~Character(){}

  /**
   * \brief Executes command
   *
   * \param [in] cmd
   *
   * \return int
   */
  virtual int doCommand(Command& cmd) = 0;
};

}; /* namespace swamp */

#endif /* SWAMP_CHARACTER_H */
/** @} */

