#include <iostream>
#include "entity.h"
#include "globals.h"

using namespace std;

const string BOLD = "\033[1m";
const string RESET = "\033[0m";

Entity::Entity(const string& name, const string& description, Entity* parent) :
	name(name), description(description), parent(parent), type(EntityType::ENTITY)
{
	if (parent != nullptr) {
		parent->contains.push_back(this);
	}
}

Entity::~Entity() { }

void Entity::SetParent(Entity* newParent) {
	if (parent == newParent) return;

	if (parent != nullptr) {
		parent->contains.remove(this);
	}

	parent = newParent;

	if (parent != nullptr) {
		parent->contains.push_back(this);
	}
}

Entity* Entity::GetParent() const {
	return parent;
}

const string& Entity::GetName() const {
	return name;
}

const string& Entity::GetDescription() const {
	return description;
}

EntityType Entity::GetType() const {
	return type;
}

void Entity::FindAllOfType(EntityType type, std::list<Entity*>& list) const {
	for (Entity* entity : contains)	{
		if (entity->GetType() == type) {
			list.push_back(entity);
		}
	}
}

void Entity::Look() const {
	PushNotification(description);
}

void Entity::Update() { return; }

Entity* Entity::Find(const string& targetName) const {
	for (Entity* entity : contains) {
		if (entity->GetName() == targetName) {
			return entity;
		}
	}
	return nullptr;
}