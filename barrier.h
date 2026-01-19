#pragma once

#include "entity.h"

class Item;

class Barrier : public Entity {
public:
	Barrier(const std::string& name, const std::string& description, Entity* key, bool isLocked, Entity* parent);
	~Barrier();

	void Open();
	void Unlock();
	bool TryUnlock(Item* item);

	bool IsOpen() const;
	bool IsLocked() const;	
	const Entity* GetKey() const;

private:
	Entity* key;
	bool isOpen;
	bool isLocked;
};