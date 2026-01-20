#pragma once

#include <list>

class Entity;
class Command;
class Player;

class World {
public:
	World();
	~World();

	Command* GetCommandSystem() const;

	void Update();

private:
	std::list<Entity*> entities;
	Player* player;
	Command* commandSystem;
};