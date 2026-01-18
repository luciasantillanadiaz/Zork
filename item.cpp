#include "item.h"

using namespace std;

Item::Item(const string& name, const string& description, Entity* parent) :
	Entity(name, description, parent)
{
	type = EntityType::ITEM;
}

Item::~Item() { }