#pragma once

#include "entity.h"

class Room;
class Item;
class Barrier;
class Exit;

class Creature : public Entity {
public:
	Creature(const std::string& name, const std::string& description, Room* room);
	~Creature();

	virtual bool Move(Direction direction);
	virtual bool Open(Barrier* barrier);
	virtual bool Take(Item* item);
	virtual bool Drop(Item* item);
	virtual bool Attack(Creature* target, Item* item);
	void ReceiveDamage(int damage);
	virtual void Die();
	void Update() override;

	bool IsAlive() const;
	int GetHealth() const;
	int GetStrength() const;
	Room* GetRoom() const;
	void SetHealth(int hp);
	void SetStrength(int str);

public:
	bool inCombat;

private:
	bool EnterRoom(const Exit* exit);
	int health;
	int strength;
};