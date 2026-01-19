#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cctype>
#include "world.h"
#include "command.h"

using namespace std;

const string BOLD = "\033[1m";
const string RESET = "\033[0m";
const string RED = "\033[31m";

vector<string> parseInput(string& input) {
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    stringstream inputStream(input);

    return vector<string>(
        istream_iterator<string>(inputStream),
        istream_iterator<string>()
    );
}

int main() {
    string input;
    vector<string> commands;

    World world;
    Command* commandSystem = world.GetCommmandSystem();

    cout << RED << BOLD << " --- WELCOME TO MY ZORK! ---\n" << RESET;

    commands.push_back("look");

    while (1) {
        if (commands.empty()) continue;

        if (commands[0] == "quit") break;

        string action = commands[0];
        vector<string> args;
        if (commands.size() > 1) {
            args.assign(commands.begin() + 1, commands.end());
        }

        commandSystem->ExecuteCommand(action, args);    

        cout << "> ";

        getline(cin, input);
        if (input.empty()) continue;

        commands = parseInput(input);
    }

    cout << "\nThanks for playing!\n";
    return 0;
}