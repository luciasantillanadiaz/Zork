#pragma once

#include <string>
#include <vector>

const std::string NOT_REC = "Command not recognized.";
const std::string NOT_INV = "You don't have that.";
const std::string NOT_HERE = "There is no such thing here.";
const std::string NOT_ITEM = "You can't use that.";
const std::string NOT_ENEMY = "There is no one to attack here.";
const std::string IN_COM = "You are in combat, you can't do that.";

void PushNotification(const std::string& msg);

extern std::vector<std::string> notificationQueue;