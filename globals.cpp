#include <string>
#include "globals.h"

using namespace std;

vector<string> notificationQueue;

void PushNotification(const string& msg) {
	notificationQueue.push_back(msg);
}