#pragma once

#include <list>
#include <vector>

class Entity;
class Command;
class Player;
class Room;

class World {
public:
	World();
	~World();

	void Update();	

	Command* GetCommandSystem() const;

private:
	std::list<Entity*> entities;
	Player* player;
	Room* endRoom;
	Command* commandSystem;
};