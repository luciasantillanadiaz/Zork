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

bool Creature::Take(Item* item) {
	if (item != nullptr) {
		item->SetParent(this);
		return true;
	}

	return false;
}

bool Creature::Drop(Item* item) {
	if (item != nullptr) {
		if (item->GetParent() == this) {
			item->SetParent(static_cast<Room*>(parent));
			return true;
		}
	}

	return false;
}

Room* Creature::GetRoom() {
	return static_cast<Room*>(parent);
}