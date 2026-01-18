#pragma once

#include "entity.h"
#include "room.h"

class Room;
class Barrier;

class Exit : public Entity {
public:
	Exit(const std::string& name, const std::string& description, Direction direction,
		Room* origin, Room* destination, bool bidirectional, Barrier* barrier);
	~Exit();

	Room* GetDestination() const;
	Direction GetDirection(const Room* room) const;
	Barrier* GetBarrier() const;

private:
	Room* origin;
	Room* destination;
	Barrier* barrier;
	Direction direction;
	bool bidirectional;
	
	static Direction GetOppositeDirection(Direction direction);
};