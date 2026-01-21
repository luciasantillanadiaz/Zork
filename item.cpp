#include <iostream>
#include "item.h"
#include "globals.h"

using namespace std;

Item::Item(const string& name, const string& description, Entity* parent) :
	Entity(name, description, parent)
{
	type = EntityType::ITEM;
	itemType = ItemType::COMMON;
	dealingDamage = 10;
}

Item::~Item() { }

ItemType Item::GetItemType() const {
	return itemType;
}

int Item::GetDealingDamage() const {
	return dealingDamage;
}

void Item::SetItemType(ItemType type) {
	itemType = type;
}

void Item::SetDealingDamage(int damage) {
	dealingDamage = damage;
}

void Item::Look() const {
	PushNotification(description);
}