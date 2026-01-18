#include <iostream>
#include "player.h"
#include "item.h"
#include "barrier.h"

using namespace std;

Player::Player(const string& name, const string& description, Room* room) :
	Creature(name, description, room)
{
	type = EntityType::PLAYER;
}

Player::~Player() { }

void Player::Unlock(Barrier* barrier, Item* key) {
	if (barrier == nullptr || key == nullptr) return;

	if (key->GetParent() != this) {
		cout << "You don't have the item " << key->GetName() << "." << endl;
		return;
	}

	if (barrier->TryUnlock(key)) {
		cout << barrier->GetName() << " is unlocked." << endl;
	}
	else {
		cout << "Try with something else." << endl;
	}
}

void Player::GetInventory() const {
	list<Entity*> inventoryList;
	FindAllOfType(EntityType::ITEM, inventoryList);

	if (inventoryList.empty()) {
		cout << "There is nothing in your inventory" << endl;
		return;
	}

	for (Entity* item : inventoryList) {
		cout << item->GetName() << ", ";
	}
	
	cout << endl;
}