#pragma once

#include "entity.h"

class Room;

class Exit : public Entity {
public:
	Exit(Direction direction, Room* origin, Room* destination, bool bidirectional);
	~Exit();

	Room* GetDestinationFrom(Room* room) const;
	Direction GetDirection(const Room* room) const;

private:
	Room* origin;
	Room* destination;
	Direction direction;
	bool bidirectional;
	
	static Direction GetOppositeDirection(Direction direction);
};