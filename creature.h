#pragma once

#include "entity.h"

class Room;
class Item;

class Creature : public Entity {
public:
	Creature(const std::string& name, const std::string& description, Room* room);
	~Creature();

	bool Move(Direction direction);
	bool Take(Item* item);
	bool Drop(Item* item);

	Room* GetRoom();
};