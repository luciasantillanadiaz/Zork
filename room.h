#pragma once

#include "entity.h"

class Exit;

class Room : public Entity {
public:
	Room(const std::string& name, const std::string& description);
	~Room();

	Exit* GetExit(Direction direction) const;
};