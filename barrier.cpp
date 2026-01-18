#include "barrier.h"

using namespace std;

Barrier::Barrier(const string& name, const string& description, Entity* key, bool isOpen, bool isLocked) :
	Entity(name, description, nullptr),
	key(key), isOpen(isOpen), isLocked(isLocked)
{
	type = EntityType::BARRIER;	
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

const Entity* Barrier::GetKey() const {
	return key;
}