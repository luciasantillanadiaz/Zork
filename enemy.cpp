#include <iostream>
#include <vector>
#include "enemy.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "globals.h"

using namespace std;
using namespace std::chrono;

Enemy::Enemy(const string& name, const string& description, Room* room) :
	Creature(name, description, room)
{
	type = EntityType::ENEMY;

    isStunned = false;
	lastMoveTime = steady_clock::now();
}

Enemy::~Enemy() { }

bool Enemy::Attack(Creature* target, Item* weapon) {
    return Creature::Attack(target, weapon);
}

int maxHealth = 0;
const int MAX_DAMAGE = 10;
const int WAIT_INTERVAL = 10;
const int STUN_DURATION = 20;
const int ROAM_INTERVAL = 60;

void Enemy::Update() {
    auto currentTime = steady_clock::now();
    auto elapsedSeconds = duration_cast<seconds>(currentTime - lastMoveTime).count();

    Player* player = PlayerInRoom();

    if (isStunned && elapsedSeconds < STUN_DURATION) {
        lastMoveTime = currentTime;
        return;
    }
    else {
        isStunned = false;
    }

    if (player != nullptr) {
        if (!inCombat && !isStunned) { 
            inCombat = true; 
            lastMoveTime = currentTime;
            maxHealth = GetHealth();
        }

        elapsedSeconds = duration_cast<seconds>(currentTime - lastMoveTime).count();
        if (elapsedSeconds >= WAIT_INTERVAL) {
            Attack(player, nullptr);
            lastMoveTime = currentTime;
        }
        if (GetHealth() <= maxHealth - MAX_DAMAGE) {
            isStunned = true;
            inCombat = false;
            player->inCombat = false;
            maxHealth = GetHealth();
            lastMoveTime = currentTime;
            PushNotification(name + " is stunned. You can move now.");
        }
        return;
    }

    if (elapsedSeconds >= ROAM_INTERVAL) {
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

    return;
}

Player* Enemy::PlayerInRoom() {
    list<Entity*> players;
    parent->FindAllOfType(EntityType::PLAYER, players);

    if (!players.empty()) { 
        return static_cast<Player*>(players.front()); 
    }

    return nullptr;
}

void Enemy::Die() {
    Creature::Die();
    parent->contains.remove(this);
    SetParent(nullptr);
}