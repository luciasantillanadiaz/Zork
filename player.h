#pragma once

#include "creature.h"

class Enemy;

class Player : public Creature {
public:
	Player(const std::string& name, const std::string& description, Room* room);
	~Player();

	void Unlock(Barrier* barrier, Item* key);
	bool EnemyIsNear();
	Enemy* EnemyInRoom();
	bool Move(Direction direction) override;
	bool Open(Barrier* barrier) override;
	bool Take(Item* item) override;
	bool Drop(Item* item) override;
	bool Attack(Creature* target, Item* weapon) override;
	void Update() override;
	void Die();

	void GetInventory() const;
};