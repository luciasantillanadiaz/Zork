#pragma once

#include <unordered_map>
#include <vector>
#include <functional>
#include "entity.h"

class Player;

using commandHandler = std::function<void(const std::vector<std::string>& args)>;

class Command {
public:
	Command();
	~Command();

	void RegisterCommands(Player* player);
	void ExecuteCommand(const std::string& command, const std::vector<std::string>& args);
	Direction GetDirectionFromString(const std::string& dir) const;

private:
	std::unordered_map<std::string, commandHandler> commands;
};