#include "exit.h"
#include "barrier.h"

using namespace std;

Exit::Exit(const string& name, const string& description, Direction direction, Room* origin, Room* destination, bool bidirectional, Barrier* barrier) :
	Entity(name, description, static_cast<Entity*>(origin)), 
	direction(direction), origin(origin), destination(destination), bidirectional(bidirectional), barrier(barrier)
{
	type = EntityType::EXIT;

	if (barrier != nullptr) {
		if (barrier->GetParent() == nullptr) {
			barrier->SetParent(this);
			contains.push_back(barrier);
		}
	}

	if (bidirectional == true) {
		destination->contains.push_back(this);
	}
}

Exit::~Exit() { }

Room* Exit::GetDestination() const {
	return destination;
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

Barrier* Exit::GetBarrier() const {
	return barrier;
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