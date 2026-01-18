#pragma once

#include "entity.h"

class Room;
class Item;
class Barrier;

class Creature : public Entity {
public:
	Creature(const std::string& name, const std::string& description, Room* room);
	~Creature();

	bool Move(Direction direction);
	void Open(Barrier* barrier);
	bool Take(Item* item);
	bool Drop(Item* item);

	Room* GetRoom() const;
};