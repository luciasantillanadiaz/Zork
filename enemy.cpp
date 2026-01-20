#include <iostream>
#include <vector>
#include "enemy.h"
#include "exit.h"
#include "room.h"

using namespace std;
using namespace std::chrono;

Enemy::Enemy(const string& name, const string& description, Room* room) :
	Creature(name, description, room)
{
	type = EntityType::ENEMY;

	lastMoveTime = steady_clock::now();
}

Enemy::~Enemy() { }

void Enemy::Update() {
    auto currentTime = steady_clock::now();
    auto elapsedSeconds = duration_cast<seconds>(currentTime - lastMoveTime).count();

    if (elapsedSeconds >= 60) {
        list<Entity*> exits;
        parent->FindAllOfType(EntityType::EXIT, exits);

        if (exits.empty()) {
            lastMoveTime = currentTime;
            return;
        }

        vector<Entity*> exitsVector(exits.begin(), exits.end());

        int randomIndex = rand() % exitsVector.size();
        Entity* randomEntity = exitsVector[randomIndex];

        Exit* chosenExit = static_cast<Exit*>(randomEntity);
        Direction dir = chosenExit->GetDirection(static_cast<Room*>(parent));

        Move(dir);

        lastMoveTime = currentTime;
    }
}