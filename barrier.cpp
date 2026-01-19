#include "barrier.h"
#include "item.h"

using namespace std;

Barrier::Barrier(const string& name, const string& description, Entity* key, bool isLocked, Entity* parent) :
	Entity(name, description, parent),
	key(key), isLocked(isLocked)
{
	type = EntityType::BARRIER;	

	isOpen = false;
}

Barrier::~Barrier() { }

void Barrier::Open() {
	isOpen = true;
}

bool Barrier::IsOpen() const {
	return isOpen;
}

void Barrier::Unlock() {
	isLocked = false;
}

bool Barrier::IsLocked() const {
	return isLocked;
}

bool Barrier::TryUnlock(Item* item) {
	if (item != key) { return false; }

	Unlock();
	return true;
}

const Entity* Barrier::GetKey() const {
	return key;
}