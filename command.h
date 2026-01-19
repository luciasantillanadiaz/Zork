#pragma once

#include <unordered_map>
#include <vector>
#include <functional>

class Player;

using commandHandler = std::function<void(const std::vector<std::string>& args)>;

class Command {
public:
	Command();
	~Command();

	void RegisterCommands(Player* player);
	void ExecuteCommand(const std::string& command, const std::vector<std::string>& args);

private:
	std::unordered_map<std::string, commandHandler> commands;
};