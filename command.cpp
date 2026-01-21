#include <iostream>
#include "command.h"
#include "player.h"
#include "room.h"
#include "enemy.h"
#include "item.h"
#include "barrier.h"
#include "globals.h"

using namespace std;

Command::Command() { }
Command::~Command() { }

void Command::RegisterCommands(Player* player) {
    // --- LOOK ---
    auto look = [player](const vector<string>& args) {
        if (args.empty()) { // look
            player->GetRoom()->Look();
            return;
        }

        if (args.size() > 1) { // look [entity]
            PushNotification(NOT_REC);
            return;
        }

        const string& targetName = args[0];

        auto findVisibleEntity = [&](const string& name) -> Entity* {
            Entity* entity = player->GetRoom()->Find(name);
            if (entity != nullptr) return entity;

            entity = player->Find(name);
            if (entity != nullptr) return entity;

            return nullptr;
        };

        Entity* entity = findVisibleEntity(targetName);

        if (entity != nullptr) {
            entity->Look();
        }
        else {
            PushNotification(NOT_INV);
        }
    };
    commands["look"] = look;
    commands["l"] = look;

    // --- WALK ---
    auto move = [this, player](const vector<string>& args) {
        if (args.empty()) { // walk [direction]
            PushNotification(NOT_REC);
            return;
        }
        else {
            player->Move(GetDirectionFromString(args[0]));
        }
    };
    commands["walk"] = move;
    commands["go"] = move;
    commands["move"] = move;

    // --- DIRECTIONS ---
    auto moveNorth = [player](const vector<string>& args) { 
        if (args.empty()) { player->Move(Direction::NORTH); }
        else { PushNotification(NOT_REC); }
    };
    commands["north"] = moveNorth; commands["n"] = moveNorth;

    auto moveSouth = [player](const vector<string>& args) { 
        if (args.empty()) { player->Move(Direction::SOUTH); }
        else { PushNotification(NOT_REC); }
    };
    commands["south"] = moveSouth; commands["s"] = moveSouth;

    auto moveEast = [player](const vector<string>& args) { 
        if (args.empty()) { player->Move(Direction::EAST); } 
        else { PushNotification(NOT_REC); }
    };
    commands["east"] = moveEast; commands["e"] = moveEast;

    auto moveWest = [player](const vector<string>& args) { 
        if (args.empty()) { player->Move(Direction::WEST); }
        else { PushNotification(NOT_REC); }
    };
    commands["west"] = moveWest; commands["w"] = moveWest;

    auto down = [player](const vector<string>& args) { 
        if (args.empty()) { player->Move(Direction::DOWN); }
        else { PushNotification(NOT_REC); }
    };
    commands["down"] = down; commands["d"] = down;

    auto up = [player](const vector<string>& args) { 
        if (args.empty()) { player->Move(Direction::UP); }
        else { PushNotification(NOT_REC); }
    };
    commands["up"] = up; commands["u"] = up;

    // --- TAKE ---
    auto take = [player](const vector<string>& args) {
        if (args.size() != 1) { // take [item]
            PushNotification(NOT_REC);
            return;
        }

        const string& itemName = args[0];

        auto getItemFromRoom = [&](const string& name) -> Item* {
            Entity* entity = player->GetRoom()->Find(name);

            if (entity == nullptr) {
                PushNotification(NOT_HERE);
                return nullptr;
            }

            if (entity->GetType() != EntityType::ITEM) {
                PushNotification("You can't take that.");
                return nullptr;
            }

            return static_cast<Item*>(entity);
        };

        Item* item = getItemFromRoom(itemName);

        if (item != nullptr) {
            player->Take(item);
        }
    };
    commands["take"] = take;
    commands["get"] = take;
    commands["pick"] = take;

    // --- DROP ---
    auto drop = [player](const vector<string>& args) {
        if (args.size() != 1) { // drop [item]
            PushNotification(NOT_REC);
            return;
        }

        const string& itemName = args[0];

        auto getItemFromInventory = [&](const string& name) -> Item* {
            Entity* entity = player->Find(name);

            if (entity == nullptr) {
                PushNotification(NOT_INV);
                return nullptr;
            }

            if (entity->GetType() != EntityType::ITEM) {
                PushNotification("You can't drop that.");
                return nullptr;
            }

            return static_cast<Item*>(entity);
        };

        Item* item = getItemFromInventory(itemName);

        if (item != nullptr) {
            player->Drop(item);
        }
    };
    commands["drop"] = drop;

    // --- PLACE ---
    auto place = [player](const vector<string>& args) {
        if (args.size() != 3 || args[1] != "in") { // place [item] in [barrier]
            PushNotification(NOT_REC);
            return;
        }

        const string& itemName = args[0];
        const string& placeName = args[2];

        auto getItemFromInventory = [&](const string& name) -> Item* {
            Entity* entity = player->Find(name);

            if (entity == nullptr) {
                PushNotification(NOT_INV);
                return nullptr;
            }

            if (entity->GetType() != EntityType::ITEM) {
                PushNotification("You can't place that.");
                return nullptr;
            }

            return static_cast<Item*>(entity);
        };

        auto getItemFromRoom = [&](const string& name) -> Barrier* {
            Entity* entity = player->GetRoom()->Find(name);

            if (entity == nullptr) {
                PushNotification(NOT_HERE);
                return nullptr;
            }

            if (entity->GetType() != EntityType::BARRIER) {
                PushNotification("You can't place something there.");
                return nullptr;
            }

            return static_cast<Barrier*>(entity);
        };

        Item* item = getItemFromInventory(itemName);
        Barrier* place = getItemFromRoom(placeName);

        if (item != nullptr) {
            player->Place(item, place);
        }
    };
    commands["place"] = place;

    // --- INVENTORY ---
    auto inventory = [player](const vector<string>& args) {
        if (!args.empty()) { // inventory
            PushNotification(NOT_REC);
            return;
        }
        player->GetInventory();
    };
    commands["inventory"] = inventory;
    commands["i"] = inventory;

    // --- HEALTH ---
    auto health = [player](const vector<string>& args) {
        if (!args.empty()) { // health
            PushNotification(NOT_REC);
            return;
        }
        PushNotification("You have " + to_string(player->GetHealth()) + " life points.");
    };
    commands["health"] = health;
    commands["h"] = health;

    // --- OPEN ---
    auto open = [player](const vector<string>& args) {
        if (args.size() != 1) { // open [barrier]
            PushNotification(NOT_REC);
            return;
        }

        const string& targetName = args[0];

        auto getOpenableBarrier = [&](const string& name) -> Barrier* {
            Entity* entity = player->GetRoom()->Find(name);

            if (entity == nullptr) {
                PushNotification(NOT_HERE);
                return nullptr;
            }

            if (entity->GetType() != EntityType::BARRIER) {
                PushNotification("You can't open that.");
                return nullptr;
            }

            return static_cast<Barrier*>(entity);
        };

        Barrier* barrier = getOpenableBarrier(targetName);

        if (barrier != nullptr) {
            player->Open(barrier);
        }
    };
    commands["open"] = open;

    // --- UNLOCK ---
    auto unlock = [player](const vector<string>& args) {
        if (args.size() != 3 || args[1] != "with") { // unlock [barrier] with [key]
            PushNotification(NOT_REC);
            return;
        }

        const string& targetName = args[0];
        const string& keyName = args[2];

        auto getBarrier = [&](const string& name) -> Barrier* {
            Entity* entity = player->GetRoom()->Find(name);

            if (entity == nullptr) {
                PushNotification(NOT_HERE);
                return nullptr;
            }
            if (entity->GetType() != EntityType::BARRIER) {
                PushNotification("You can't unlock that.");
                return nullptr;
            }
            return static_cast<Barrier*>(entity);
        };

        auto getKey = [&](const string& name) -> Item* {
            Entity* entity = player->Find(name);

            if (entity == nullptr) {
                PushNotification(NOT_INV);
                return nullptr;
            }
            if (entity->GetType() != EntityType::ITEM) {
                PushNotification(NOT_ITEM);
                return nullptr;
            }
            return static_cast<Item*>(entity);
        };

        Barrier* barrier = getBarrier(targetName);
        if (barrier == nullptr) { return; }

        Item* key = getKey(keyName);
        if (key == nullptr) { return; }

        player->Unlock(barrier, key);        
    };
    commands["unlock"] = unlock;

    // --- ATTACK ---
    auto attack = [this, player](const vector<string>& args) {
        if (!player->inCombat) {
            PushNotification(NOT_ENEMY);
            return;
        }

        auto getWeapon = [&](const string& name) -> Item* {
            Entity* entity = player->Find(name);

            if (!entity) { 
                PushNotification(NOT_INV); 
                return nullptr; }

            if (entity->GetType() != EntityType::ITEM) { 
                PushNotification(NOT_ITEM);
                return nullptr; 
            }

            Item* item = static_cast<Item*>(entity);
            if (item->GetItemType() != ItemType::WEAPON) { 
                PushNotification(NOT_ITEM);
                return nullptr; 
            }

            return item;
        };

        auto getTarget = [&](const string& name) -> Enemy* {
            if (name.empty()) {
                list<Entity*> enemies;
                player->GetRoom()->FindAllOfType(EntityType::ENEMY, enemies);
                
                if (enemies.empty()) { 
                    PushNotification(NOT_ENEMY); 
                    return nullptr; 
                }

                if (enemies.size() > 1) { 
                    PushNotification("Choose one enemy to attack."); 
                    return nullptr; 
                }

                return static_cast<Enemy*>(enemies.front());
            }
            else {
                Entity* entity = player->GetRoom()->Find(name);
                if (!entity || entity->GetType() != EntityType::ENEMY) {
                    PushNotification(NOT_ENEMY);
                    return nullptr;
                }
                return static_cast<Enemy*>(entity);
            }
        };

        string targetName = "";
        string weaponName = "";

        switch (args.size()) {
        case 0: // attack
            break;
        case 1: // attack [enemy]
            targetName = args[0];
            break;
        case 2: // attack with [weapon]
            if (args[0] != "with") { 
                PushNotification(NOT_REC); 
                return; 
            }
            weaponName = args[1];
            break;
        case 3: // attack [enemy] with [weapon]
            if (args[1] != "with") { 
                PushNotification(NOT_REC); 
                return; 
            }
            targetName = args[0];
            weaponName = args[2];
            break;
        default:
            PushNotification(NOT_REC);
            return;
        }

        Item* weapon = nullptr;
        if (!weaponName.empty()) {
            weapon = getWeapon(weaponName);
            if (weapon == nullptr) { return; }
        }

        Enemy* target = getTarget(targetName);
        if (target != nullptr) {
            player->Attack(target, weapon);
        }
    };
    commands["attack"] = attack;
    commands["fight"] = attack;
}

void Command::ExecuteCommand(const string& command, const vector<string>& args) {
	auto it = commands.find(command);

	if (it != commands.end()) {
		it->second(args);
	}
	else {
		PushNotification(NOT_REC);
	}
}

Direction Command::GetDirectionFromString(const string& dir) const {
    if (dir == "north" || dir == "n") return Direction::NORTH;
    if (dir == "south" || dir == "s") return Direction::SOUTH;
    if (dir == "east" || dir == "e") return Direction::EAST;
    if (dir == "west" || dir == "w") return Direction::WEST;
    if (dir == "up" || dir == "u") return Direction::UP;
    if (dir == "down" || dir == "d") return Direction::DOWN;

    return Direction::UNKNOWN;
}

