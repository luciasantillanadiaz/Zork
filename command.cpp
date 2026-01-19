#include <iostream>
#include "command.h"
#include "player.h"
#include "room.h"

using namespace std;

Command::Command() { }
Command::~Command() { }

void Command::RegisterCommands(Player* player) {
	auto look = [player](const vector<string>& args) {
		player->GetRoom()->Look();
	};
	commands["look"] = look;

	auto moveNorth = [player](const vector<string>& args) {
		player->Move(Direction::NORTH);
	};
	commands["north"] = moveNorth;
	commands["n"] = moveNorth;

	auto moveSouth = [player](const vector<string>& args) {
		player->Move(Direction::SOUTH);
	};
	commands["south"] = moveSouth;
	commands["s"] = moveSouth;

	auto moveEast = [player](const vector<string>& args) {
		player->Move(Direction::EAST);
	};
	commands["east"] = moveEast;
	commands["e"] = moveEast;

	auto moveWest = [player](const vector<string>& args) {
		player->Move(Direction::WEST);
	};
	commands["west"] = moveWest;
	commands["w"] = moveWest;
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

