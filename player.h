#pragma once

#include "creature.h"

class Player : public Creature {
public:
	Player(const std::string& name, const std::string& description, Room* room);
	~Player();

	void Unlock(Barrier* barrier, Item* key);

	void GetInventory() const;
};
