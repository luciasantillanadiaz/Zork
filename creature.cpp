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
	if (barrier == nullptr) { return; }

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

Room* Creature::GetRoom() const {
	return static_cast<Room*>(parent);
}