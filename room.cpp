#include <iostream>
#include "room.h"
#include "exit.h"
#include "globals.h"
#include "barrier.h"

using namespace std;

Room::Room(const string& name, const string& description) :
	Entity(name, description, nullptr)
{
	type = EntityType::ROOM;
}

Room::~Room() { }

void Room::Look() const {
	PushNotification(name);
	Entity::Look();

	for (Entity* entity : contains) {
		if (entity->GetType() == EntityType::PLAYER) { return; }

		if (entity->GetType() == EntityType::EXIT) {
			for (Entity* e : entity->contains) {
				PushNotification("There is a " + e->GetName() + ".");
			}
		}
		else {
			PushNotification("There is a " + entity->GetName() + ".");
		}
	}
}

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

Entity* Room::Find(const string& targetName) const {
	for (Entity* entity : contains) {
		if (entity->GetName() == targetName) {
			return entity;
		}
	}

	list<Entity*> exits;
	FindAllOfType(EntityType::EXIT, exits);
	for (Entity* exit : exits) {
		for (Entity* c : exit->contains) {
			if (c->GetName() == targetName) {
				return c;
			}
		}
	}

	return nullptr;
}