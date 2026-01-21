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
        switch (args.size()) {
        case 0: {
            player->GetRoom()->Look();
            break;
        }
        case 1: {
            Entity* entity = player->GetRoom()->Find(args[0]);

            if (entity == nullptr) {
                entity = player->Find(args[0]);
            }

            if (entity == nullptr) {
                PushNotification("There is nothing like that here.");
            }
            else {
                entity->Look();
            }
            break;
        }
        default:
            PushNotification("Command not recognized.");
        }
    };
    commands["look"] = look;
    commands["l"] = look;

    // --- WALK ---
    auto move = [this, player](const vector<string>& args) {
        if (args.empty()) {
            PushNotification("Walk where?");
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
    auto moveNorth = [player](const vector<string>& args) { player->Move(Direction::NORTH); };
    commands["north"] = moveNorth; commands["n"] = moveNorth;

    auto moveSouth = [player](const vector<string>& args) { player->Move(Direction::SOUTH); };
    commands["south"] = moveSouth; commands["s"] = moveSouth;

    auto moveEast = [player](const vector<string>& args) { player->Move(Direction::EAST); };
    commands["east"] = moveEast; commands["e"] = moveEast;

    auto moveWest = [player](const vector<string>& args) { player->Move(Direction::WEST); };
    commands["west"] = moveWest; commands["w"] = moveWest;

    auto down = [player](const vector<string>& args) { player->Move(Direction::DOWN); };
    commands["down"] = down; commands["d"] = down;

    auto up = [player](const vector<string>& args) { player->Move(Direction::UP); };
    commands["up"] = up; commands["u"] = up;

    // --- TAKE ---
    auto take = [player](const vector<string>& args) {
        switch (args.size()) {
        case 1: {
            Entity* entity = player->GetRoom()->Find(args[0]);
            if (entity == nullptr) {
                PushNotification("You can't take that.");
                return;
            }
            if (entity->GetType() != EntityType::ITEM) {
                PushNotification(entity->GetName() + " is not an item.");
                return;
            }
            player->Take(static_cast<Item*>(entity));
            break;
        }
        default:
            PushNotification("Command not recognized.");
            break;
        }
    };
    commands["take"] = take;

    // --- DROP ---
    auto drop = [player](const vector<string>& args) {
        switch (args.size()) {
        case 1: {
            Entity* entity = player->Find(args[0]);
            if (entity == nullptr) {
                PushNotification("You don't possess this item.");
                return;
            }
            if (entity->GetType() != EntityType::ITEM) {
                PushNotification(entity->GetName() + " is not an item.");
                return;
            }
            player->Drop(static_cast<Item*>(entity));
            break;
        }
        default:
            PushNotification("Command not recognized.");
        }
    };
    commands["drop"] = drop;

    // --- INVENTORY ---
    auto inventory = [player](const vector<string>& args) {
        if (!args.empty()) {
            PushNotification("Command not recognized.");
            return;
        }
        player->GetInventory();
    };
    commands["inventory"] = inventory;
    commands["i"] = inventory;

    // --- OPEN ---
    auto open = [player](const vector<string>& args) {
        if (args.size() != 1) {
            PushNotification("Command not recognized");
            return;
        }

        Entity* entity = player->GetRoom()->Find(args[0]);
        if (entity == nullptr) {
            PushNotification("You can't open that");
            return;
        }

        if (entity->GetType() != EntityType::BARRIER) {
            PushNotification("You can't open that");
            return;
        }

        player->Open(static_cast<Barrier*>(entity));
    };
    commands["open"] = open;

    // --- UNLOCK ---
    auto unlock = [player](const vector<string>& args) {
        if (args.size() != 3) {
            PushNotification("Command not recognized.");
            return;
        }

        if (args[1] != "with") {
            PushNotification("Command not recognized.");
            return;
        }

        Entity* entity = player->GetRoom()->Find(args[0]);
        if (entity == nullptr) {
            PushNotification("You can't unlock that.");
            return;
        }

        if (entity->GetType() != EntityType::BARRIER) {
            PushNotification("You can't unlock that");
            return;
        }

        Entity* entityItem = player->Find(args[2]);
        if (entityItem == nullptr) {
            PushNotification("You don't possess this item.");
            return;
        }

        if (entityItem->GetType() != EntityType::ITEM) {
            PushNotification("You can't use that.");
            return;
        }

        player->Unlock(static_cast<Barrier*>(entity), static_cast<Item*>(entityItem));
    };
    commands["unlock"] = unlock;
}

void Command::ExecuteCommand(const string& command, const vector<string>& args) {
	auto it = commands.find(command);

	if (it != commands.end()) {
		it->second(args);
	}
	else {
		cout << "Command not recognized.\n";
	}
}

Direction Command::GetDirectionFromString(const string& dir) {
    if (dir == "north" || dir == "n") return Direction::NORTH;
    if (dir == "south" || dir == "s") return Direction::SOUTH;
    if (dir == "east" || dir == "e") return Direction::EAST;
    if (dir == "west" || dir == "w") return Direction::WEST;
    if (dir == "up" || dir == "u") return Direction::UP;
    if (dir == "down" || dir == "d") return Direction::DOWN;

    return Direction::UNKNOWN;
}

