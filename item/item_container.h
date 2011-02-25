/** \file item_container.h */
#ifndef SWAMP_ITEM_CONTAINER_H
#define SWAMP_ITEM_CONTAINER_H

/**\addtogroup item */
/** @{ */

#include <stddef.h>
#include <tr1/unordered_map>

#include "item.h"

/**
 * \namespace swamp
 */
namespace swamp
{

/**
 * \class ItemContainer
 * \ingroup item
 *
 * \brief Class representing items container
 */
class ItemContainer : public Item
{
  public:
    ItemContainer();
    virtual ~ItemContainer();

    const item_type_t& getType() const;
    void setType(const item_type_t& type);

    const item_slot_t& getSlot() const;
    void setSlot(const item_slot_t& slot);

    const size_t& getWeight() const;
    void setWeight(const size_t weight);

    const size_t& getValue() const;
    void setValue(const size_t& value);

  private:
    /**
     * \typedef items_container_t
     * \ingroup item
     */
    typedef std::unordered_map<size_t /* index */, item_t*> items_container_t;

  private:
    items_container_t m_items;

};

}; /* namespace swamp */

#endif /* SWAMP_ITEM_H */
/** @} */
