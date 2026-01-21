#pragma once

#include <chrono>
#include "creature.h"

class Room;
class Item;
class Player;

class Enemy : public Creature {
public:
	Enemy(const std::string& name, const std::string& description, Room* room);
	~Enemy();

	bool Attack(Creature* target, Item* weapon);
	void Update() override;
	Player* PlayerInRoom();
	void Die();

public:
	bool isStunned;

private:
	std::chrono::steady_clock::time_point lastMoveTime;
};