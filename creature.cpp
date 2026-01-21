#include <iostream>
#include "creature.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "barrier.h"

using namespace std;

Creature::Creature(const string& name, const string& description, Room* room) :
	Entity(name, description, static_cast<Entity*>(room))
{
	type = EntityType::CREATURE;
	health = 10;
	strength = 1;
	inCombat = false;
}

Creature::~Creature() { }

bool Creature::Move(Direction direction) {
	Room* currentRoom = dynamic_cast<Room*>(parent);
	if (currentRoom == nullptr) { return false; }

	Exit* exit = currentRoom->GetExit(direction);

	if (exit == nullptr) { return false; }

	list<Entity*> barriers;
	exit->FindAllOfType(EntityType::BARRIER, barriers);

	if (barriers.empty()) { return EnterRoom(exit); }

	Barrier* barrier = static_cast<Barrier*>(barriers.front());

	if (barrier == nullptr) { return EnterRoom(exit); }

	if (barrier->IsOpen()) { return EnterRoom(exit); }

	return false;	
}

bool Creature::EnterRoom(Exit* exit) {
	Room* nextRoom = exit->GetDestinationFrom(static_cast<Room*>(parent));

	if (nextRoom == nullptr) { return false; }

	SetParent(nextRoom);
	return true;
}

bool Creature::Open(Barrier* barrier) {
	if (barrier == nullptr) { return false; }

	if (!barrier->IsLocked()) {
		barrier->Open();
		return true;
	}
	
	return false;
}

bool Creature::Take(Item* item) {
	if (item == nullptr) { return false; }

	if (item->GetParent() != parent) { return false; }

	item->SetParent(this);
	return true;
}

bool Creature::Drop(Item* item) {
	if (item == nullptr) { return false; }

	if (item->GetParent() != this) { return false; }

	item->SetParent(parent);
	return true;
}

bool Creature::Attack(Creature* target, Item* weapon) { 
	if (target == nullptr) { return false; }

	if (target->GetRoom() != parent) { return false; }

	return true;
}

void Creature::ReceiveDamage(int damage) {
	health -= damage;

	if (IsAlive() == false) {
		Die();
	}		
}

void Creature::Die() {
	cout << name << "has died.\n";
}

bool Creature::IsAlive() const {
	return health > 0;
}

Room* Creature::GetRoom() const {
	return static_cast<Room*>(parent);
}

int Creature::GetHealth() const {
	return health;
}

int Creature::GetStrength() const {
	return strength;
}

void Creature::SetHealth(int hp) {
	health = hp;
}

void Creature::SetStrength(int str) {
	strength = str;
}