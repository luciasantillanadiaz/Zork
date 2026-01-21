#include <iostream>
#include <algorithm>
#include "room.h"
#include "exit.h"
#include "globals.h"
#include "barrier.h"
#include "item.h"

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
		else if (entity->GetType() == EntityType::BARRIER) {
			PushNotification("There is a " + entity->GetName() + ".");

			Barrier* barrier = static_cast<Barrier*>(entity);
			if (!barrier->IsOpen()) { continue; }

			for (Entity* item : barrier->contains) {
				if (item->GetType() == EntityType::ITEM) {
					PushNotification("Inside there is a " + item->GetName() + ".");
				}
			}
		}
		else {
			PushNotification("There is a " + entity->GetName() + ".");
		}
	}
}

Exit* Room::GetExit(Direction direction) {
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

Entity* Room::Find(const string& targetName) {
	Entity* ret;

	ret = Entity::Find(targetName);
	if (ret != nullptr) { return ret; }

	ret = FindInExit(targetName);	
	if (ret != nullptr) { return ret; }

	ret = FindInBarrier(targetName);
	if (ret != nullptr) { return ret; }

	return nullptr;
}

Entity* Room::FindInExit(const string& targetName) {
	list<Entity*> exits;
	FindAllOfType(EntityType::EXIT, exits);
	for (Entity* exit : exits) {
		Exit* e = static_cast<Exit*>(exit);
		Entity* ret = e->Find(targetName);

		if (ret != nullptr) { return ret; }
	}
	return nullptr;
}

Entity* Room::FindInBarrier(const string& targetName) {
	list<Entity*> barriers;
	FindAllOfType(EntityType::BARRIER, barriers);

	for (Entity* barrier : barriers) {
		Barrier* b = static_cast<Barrier*>(barrier);
		Entity* ret = b->Find(targetName);

		if (ret != nullptr) { return ret; }
	}
	return nullptr;
}

void Room::FindAllTakeable(list<Item*>& items) {
	for (Entity* entity : contains) {
		if (entity->GetType() == EntityType::ITEM) { 
			items.push_back(static_cast<Item*>(entity)); 
			continue;
		}

		if (entity->GetType() == EntityType::BARRIER) {
			Barrier* b = static_cast<Barrier*>(entity);

			if (!b->IsOpen()) { continue; }

			for (Entity* i : b->contains) {
				if (i->GetType() == EntityType::ITEM) {
					items.push_back(static_cast<Item*>(i));
					continue;
				}
			}			
		}
	}

	return;
}

void Room::Update() {
	Entity::Update();

	if (customUpdate) {
		customUpdate();
	}
}

void Room::SetCustomUpdate(function<void()> updateLogic) {
	customUpdate = updateLogic;
}