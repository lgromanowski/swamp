/** \file character/character.h */
#ifndef SWAMP_CHARACTER_H
#define SWAMP_CHARACTER_H

#include <map>
#include <vector>
#include <string>

/**\addtogroup character */
/** @{ */

/**
 * \namespace swamp
 */
namespace swamp {

struct Command {
  const char* m_param_str;
};

/**
 * \struct Language
 */
struct Language {
  /**
   * \typedef translate_fun_f
   */
  //typedef int (Language::translate_fun_f*)(const char* input_str, char* output_str);

  unsigned int m_race_id;                   /**< */
};

/**
 * \struct BasicAttributes
 * \ingroup character
 *
 * \brief .
 */
struct BasicAttributes {
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
 * \todo This class sucks, it should be modified
 */
struct Level {
  unsigned int m_experience_points;
  unsigned int m_level;
};

/**
 * \struct Skill
 * \ingroup character
 */
struct Skill {
  unsigned int m_skill_id;
};

/**
 * \struct Punishment
 * \ingroup character
 */
struct Punishment {
  unsigned int m_punishment_id;
  BasicAttributes m_attributes;
};

/**c
 * \struct CharacterRace
 * \ingroup character
 *
 * \brief
 */
struct CharacterRace {
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
struct CharacterClass {
  unsigned int m_class_id;
	const char* m_name;
  BasicAttributes m_class_attributes;
};

typedef std::map<unsigned int /* level */, std::vector<CharacterClass*>> LevelTree;

struct CharacterDeity {
	unsigned int m_deity_id;
	const char* m_name_str;
};

/**
 * \struct Character
 * \ingroup character
 *
 * \brief Base class for game characters (player, npc).
 */
struct Character {
  /**
   * \brief character class destructor
   */
  virtual ~Character(){}

	virtual int write(const std::string& text) = 0;
};

}; /* namespace swamp */

#endif /* SWAMP_CHARACTER_H */
/** @} */

