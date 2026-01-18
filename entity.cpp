#include "entity.h"

using namespace std;

Entity::Entity(const string& name, const string& description, Entity* parent) :
	name(name), description(description), parent(parent), type(EntityType::ENTITY)
{
	if (parent != nullptr) {
		parent->contains.push_back(this);
	}
}

Entity::~Entity() {
	if (parent != nullptr) {
		parent->contains.remove(this);
	}

	for (Entity* child : contains) {
		child->parent = nullptr;
	}
}

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