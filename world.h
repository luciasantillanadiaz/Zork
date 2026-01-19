#pragma once

#include <list>

class Entity;
class Command;
class Player;

class World {
public:
	World();
	~World();

	Command* GetCommmandSystem() const;

private:
	std::list<Entity*> entities;
	Player* player;
	Command* commandSystem;
};