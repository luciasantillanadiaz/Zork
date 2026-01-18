#include "room.h"
#include "exit.h"

using namespace std;

Room::Room(const string& name, const string& description) :
	Entity(name, description, nullptr)
{
	type = EntityType::ROOM;
}

Room::~Room() { }

Exit* Room::GetExit(Direction direction) const {
	for (Entity* e : contains) {
		if (e->GetType() == EntityType::EXIT) {
			Exit* exit = static_cast<Exit*>(e);
			if (exit->GetDirection(this) == direction) {
				return exit;
			}
		}
	}
	return nullptr;
}