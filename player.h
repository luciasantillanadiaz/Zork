#pragma once

#include "creature.h"

class Player : public Creature {
public:
	Player(const std::string& name, const std::string& description, Room* room);
	~Player();

	void Unlock(Barrier* barrier, Item* key);
	bool Move(Direction direction) override;
	bool Open(Barrier* barrier) override;
	bool Take(Item* item) override;
	bool Drop(Item* item) override;

	void GetInventory() const;
};