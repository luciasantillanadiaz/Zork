#include <iostream>
#include "player.h"
#include "item.h"
#include "barrier.h"
#include "room.h"

using namespace std;

Player::Player(const string& name, const string& description, Room* room) :
	Creature(name, description, room)
{
	type = EntityType::PLAYER;
}

Player::~Player() { }

void Player::Unlock(Barrier* barrier, Item* key) {
	if (barrier == nullptr || key == nullptr) { return; }

	if (key->GetParent() != this) {
		cout << "You don't have the item " << key->GetName() << ".\n";
		return;
	}

	if (barrier->TryUnlock(key)) {
		cout << barrier->GetName() << " is unlocked.\n";
	}
	else {
		cout << "Try with something else.\n";
	}
}

bool Player::Move(Direction direction) {
	Room* room = GetRoom();

	Exit* exit = room->GetExit(direction);

	if (exit == nullptr) {
		cout << "There is a wall.\n";
		return false;
	}

	bool success = Creature::Move(direction);

	if (success) {
		GetRoom()->Look();
	}
	else {
		cout << "It's closed.\n";
	}

	return success;
}

bool Player::Open(Barrier* barrier) {
	bool success = Creature::Open(barrier);

	if (success) {
		cout << "You opened " << barrier->GetName() << ".\n";

		list<Entity*> items;
		barrier->FindAllOfType(EntityType::ITEM, items);

		if (items.empty()) { return success; }

		cout << "You found: ";

		for (Entity* item : items) {
			item->SetParent(parent);
			cout << item->GetName() << " ";
		}

		cout << "\n";
	}
	else {
		cout << "It's locked.\n";
	}

	return success;
}

bool Player::Take(Item* item) {
	bool success = Creature::Take(item);

	if (success) {
		cout << "You take " << item->GetName() << ".\n";
	}
	else {
		cout << "There is nothing like that here.\n";
	}

	return success;
}

bool Player::Drop(Item* item) {
	bool success = Creature::Drop(item);

	if (success) {
		cout << "You dropped " << item->GetName() << ".\n";
	}
	else {
		cout << "You don't have the item " << item->GetName() << ".\n";
	}

	return success;
}

void Player::GetInventory() const {
	list<Entity*> inventoryList;
	FindAllOfType(EntityType::ITEM, inventoryList);

	if (inventoryList.empty()) {
		cout << "There is nothing in your inventory.\n";
		return;
	}

	for (Entity* item : inventoryList) {
		cout << item->GetName() << ", ";
	}
	
	cout << ".\n";
}