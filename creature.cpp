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
}

Creature::~Creature() { }

bool Creature::Move(Direction direction) {
	Exit* exit = static_cast<Room*>(parent)->GetExit(direction);

	if (exit != nullptr) {
		Barrier* barrier = exit->GetBarrier();

		if (barrier != nullptr) {

			if (barrier->IsOpen()) {
				Room* nextRoom = exit->GetDestinationFrom(static_cast<Room*>(parent));

				if (nextRoom != nullptr) {
					SetParent(nextRoom);
					return true;
				}
			}
		}		
	}

	return false;
}

void Creature::Open(Barrier* barrier) {
	if (barrier == nullptr) return;

	if (!barrier->IsLocked()) {
		barrier->Open();
	}
	else {
		cout << barrier->GetName() << " is locked." << endl;
	}
}

bool Creature::Take(Item* item) {
	if (item != nullptr) {
		item->SetParent(this);
		return true;
	}

	return false;
}

bool Creature::Drop(Item* item) {
	if (item == nullptr) return false;

	if (item->GetParent() != this) {
		cout << "You don't have the item " << item->GetName() << "." << endl;
		return false;
	}

	item->SetParent(parent);
	return true;
}

Room* Creature::GetRoom() const{
	return static_cast<Room*>(parent);
}