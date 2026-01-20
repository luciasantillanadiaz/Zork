#pragma once

#include <chrono>
#include "creature.h"

class Room;

class Enemy : public Creature {
public:
	Enemy(const std::string& name, const std::string& description, Room* room);
	~Enemy();

	void Update();

private:
	std::chrono::steady_clock::time_point lastMoveTime;
};