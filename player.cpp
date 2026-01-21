#include <iostream>
#include "player.h"
#include "item.h"
#include "barrier.h"
#include "room.h"
#include "exit.h"
#include "globals.h"
#include "enemy.h"

using namespace std;

Player::Player(const string& name, const string& description, Room* room) :
	Creature(name, description, room)
{
	type = EntityType::PLAYER;
}

Player::~Player() { }

void Player::Unlock(Barrier* barrier, Item* key) {
	if (inCombat) {
		PushNotification(IN_COM);
		return;
	}

	if (barrier == nullptr || key == nullptr) { return; }

	if (key->GetParent() != this) {
		PushNotification(NOT_INV);
		return;
	}

	if (barrier->TryUnlock(key)) {
		PushNotification(barrier->GetName() + " is unlocked.");
	}
	else {
		PushNotification("Try with something else.");
	}
}

bool Player::Move(Direction direction) {
	if (inCombat) {
		PushNotification(IN_COM);
		return false;
	}

	Room* room = GetRoom();
	Exit* exit = room->GetExit(direction);

	if (exit == nullptr) {
		PushNotification("There is a wall.");
		return false;
	}

	bool success = Creature::Move(direction);

	if (success) {
		GetRoom()->Look();
		if (EnemyIsNear()) {
			PushNotification("Footsteps can be heard nearby...");
		}
	}
	else {
		PushNotification("It's closed.");
	}

	return success;
}

bool Player::Open(Barrier* barrier) {
	if (inCombat) {
		PushNotification(IN_COM);
		return  false;
	}

	if (barrier == nullptr) {
		PushNotification(NOT_HERE);
		return false;
	}

	if (barrier->IsOpen()) {
		PushNotification(barrier->GetName() + " it's already open.");
		return false;
	}

	bool success = Creature::Open(barrier);

	if (success) {
		PushNotification("You opened " + barrier->GetName() + ".");

		list<Entity*> items;
		barrier->FindAllOfType(EntityType::ITEM, items);

		if (items.empty()) { return success; }

		string print = "You found: ";

		for (Entity* item : items) {
			item->SetParent(parent);
			print += item->GetName() + " ";
		}

		PushNotification(print);
	}
	else {
		PushNotification("It's locked.");
	}

	return success;
}

bool Player::Take(Item* item) {
	bool success = Creature::Take(item);

	if (success) {
		PushNotification("You take " + item->GetName() + ".");
	}
	else {
		PushNotification(NOT_HERE);
	}

	return success;
}

bool Player::Drop(Item* item) {
	bool success = Creature::Drop(item);

	if (success) {
		PushNotification("You dropped " + item->GetName() + ".");
	}
	else {
		PushNotification(NOT_INV);
	}

	return success;
}

bool Player::Attack(Creature* target, Item* weapon) {
	if (weapon != nullptr) {
		if (weapon->GetParent() != this) {
			PushNotification(NOT_INV);
			return false;
		}

		if (weapon->GetItemType() != ItemType::WEAPON) {
			PushNotification(NOT_ITEM);
			return false; 
		}
		PushNotification("You attacked with " + weapon->GetName() + ".");
		return Creature::Attack(target, weapon);
	}
		
	PushNotification("You attacked bare-handed.");
	return Creature::Attack(target, weapon);
}

void Player::GetInventory() const {
	list<Entity*> inventoryList;
	FindAllOfType(EntityType::ITEM, inventoryList);

	if (inventoryList.empty()) {
		PushNotification("There is nothing in your inventory.");
		return;
	}

	string print = "";
	for (Entity* item : inventoryList) {
		 print += item->GetName() + " ";
	}
	
	PushNotification(print);
}

void Player::Update() {
	Enemy* enemy = EnemyInRoom();
	if (enemy != nullptr) {
		if (!inCombat && !enemy->isStunned) {
			inCombat = true;
			PushNotification("The enemy is staring at you, ready to fight.");
		}
		return;
	}
	else {
		inCombat = false;
	}
}

bool Player::EnemyIsNear() {
	list<Entity*> exits;
	parent->FindAllOfType(EntityType::EXIT, exits);

	for (Entity* exit : exits) {
		Exit* ex = static_cast<Exit*>(exit);
		Room* room = ex->GetDestinationFrom(static_cast<Room*>(parent));

		if (room == nullptr) { continue; }

		list<Entity*> enemies;
		room->FindAllOfType(EntityType::ENEMY, enemies);

		if (!enemies.empty()) { return true; }
	}

	return false;
}

Enemy* Player::EnemyInRoom() {
	list<Entity*> enemies;
	parent->FindAllOfType(EntityType::ENEMY, enemies);

	if (!enemies.empty()) { 
		return static_cast<Enemy*>(enemies.front()); 
	}

	return nullptr;
}

void Player::Die() {
	PushNotification("YOU DIED!");
	PushNotification("THE END");
}