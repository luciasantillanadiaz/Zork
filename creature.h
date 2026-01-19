#pragma once

#include "entity.h"

class Room;
class Item;
class Barrier;
class Exit;

class Creature : public Entity {
public:
	Creature(const std::string& name, const std::string& description, Room* room);
	~Creature();

	virtual bool Move(Direction direction);
	virtual bool Open(Barrier* barrier);
	virtual bool Take(Item* item);
	virtual bool Drop(Item* item);

	Room* GetRoom() const;

private:
	bool EnterRoom(Exit* exit);
};