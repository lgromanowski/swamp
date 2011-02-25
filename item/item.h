/** \file item.h */
#ifndef SWAMP_ITEM_H
#define SWAMP_ITEM_H

/**\addtogroup item */
/** @{ */

#include <stddef.h>
#include <vector>

/**
 * \namespace swamp
 */
namespace swamp
{

/**
 * \enum item_type_e
 * \ingroup item
 *
 * \brief Item types
 */
typedef enum item_type_e
{
  ITEM_TYPE_UNKNOWN = 0,                  /**< */
  ITEM_TYPE_CONTAINER,                    /**< */
  ITEM_TYPE_POTION,                       /**< */
  ITEM_TYPE_FOOD,                         /**< */
  ITEM_TYPE_ARMOR,                        /**< */
  ITEM_TYPE_WEAPON,                       /**< */
  ITEM_TYPE_STAFF,                        /**< */
  ITEM_TYPE_JEWELLERY,                    /**< */
  ITEM_TYPE_TOOL,                         /**< */
  ITEM_TYPE_KEY,                          /**< */
  ITEM_TYPE_DOCUMENT                      /**< */

} item_type_t;

/**
 * \enum item_slot_t
 * \ingroup item
 */
enum item_slot_t
{
  ITEM_SLOT_HEAD = 0,
  ITEM_SLOT_NECK,
  ITEM_SLOT_CHEST,
  ITEM_SLOT_HAND_LEFT,
  ITEM_SLOT_HAND_RIGHT,
  ITEM_SLOT_HAND_FINGERS_LEFT,
  ITEM_SLOT_HAND_FINGERS_RIGHT,
  ITEM_SLOT_LEG_LEFT,
  ITEM_SLOT_LEG_RIGHT,
  ITEM_SLOT_FEET_LEFT,
  ITEM_SLOT_FEET_RIGHT,
  ITEM_SLOT_TAIL
};

/**
 * \struct item
 * \ingroup item
 */
struct Item
{
  virtual ~Item() {}

  virtual const item_type_t& getType() const = 0;
  virtual void setType(const item_type_t& /*type*/) = 0;

  virtual const item_slot_t& getSlot() const = 0;
  virtual void setSlot(const item_slot_t& /*slot*/) = 0;

  virtual const size_t& getWeight() const = 0;
  virtual void setWeight(const size_t /*weight*/) = 0;

  virtual const size_t& getValue() const = 0;
  virtual void setValue(const size_t& /*value*/) = 0;
};

}; /* namespace swamp */

#endif /* SWAMP_ITEM_H */
/** @} */
