#pragma once

#include "entity.h"

enum class ItemType {
	WEAPON,
	COMMON
};

class Item : public Entity {
public: 
	Item(const std::string& name, const std::string& description, Entity* parent);
	~Item();

	ItemType GetItemType() const;
	int GetDealingDamage() const;
	void SetItemType(const ItemType type);
	void SetDealingDamage(const int damage);
	void Look() const;

private:
	ItemType itemType;
	int dealingDamage;
};