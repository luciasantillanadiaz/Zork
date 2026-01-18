#pragma once

#include "entity.h"

class Item : public Entity {
public: 
	Item(const std::string& name, const std::string& description, Entity* parent);
	~Item();
};