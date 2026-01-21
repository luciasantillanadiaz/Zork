#include "exit.h"
#include "room.h"

using namespace std;

Exit::Exit(Direction direction, Room* origin, Room* destination, bool bidirectional) :
	Entity("Exit", origin->GetName() + " - " + destination->GetName(), static_cast<Entity*>(origin)),
	direction(direction), origin(origin), destination(destination), bidirectional(bidirectional)
{
	type = EntityType::EXIT;

	if (bidirectional == true) {
		destination->contains.push_back(this);
	}
}

Exit::~Exit() { }

Room* Exit::GetDestinationFrom(const Room* room) const {
	if (room == origin) {
		return destination;
	}
	else if (room == destination) {
		return origin;
	}

	return nullptr;
}

Direction Exit::GetDirection(const Room* room) const {
	if (room == origin) {
		return direction;
	}
	else if (room == destination) {
		return GetOppositeDirection(direction);
	}
	return Direction::UNKNOWN;
}

Direction Exit::GetOppositeDirection(Direction direction) {
	switch (direction) {
		case Direction::NORTH: return Direction::SOUTH;
		case Direction::SOUTH: return Direction::NORTH;
		case Direction::EAST:  return Direction::WEST;
		case Direction::WEST:  return Direction::EAST;
		case Direction::UP:    return Direction::DOWN;
		case Direction::DOWN:  return Direction::UP;
		default: return Direction::UNKNOWN;
	}
}