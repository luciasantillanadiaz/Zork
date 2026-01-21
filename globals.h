#pragma once

#include <string>
#include <vector>

void PushNotification(const std::string& msg);

extern std::vector<std::string> notificationQueue;