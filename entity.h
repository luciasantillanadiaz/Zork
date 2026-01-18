#pragma once

#include <string>
#include <list>

enum class EntityType {
	ENTITY,
	PLAYER,
	ROOM,
	ITEM,
	EXIT,
	BARRIER
};

enum class Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
	UP,
	DOWN,
	UNKNOWN
};

class Entity {
public:
	Entity(const std::string& name, const std::string& description, Entity* parent);
	virtual ~Entity();

	void SetParent(Entity* newParent);
	Entity* GetParent() const;

	const std::string& GetName() const;
	const std::string& GetDescription() const;
	EntityType GetType() const;

protected:
	EntityType type;
	std::string name;
	std::string description;

	Entity* parent;

public:
	std::list<Entity*> contains;
};