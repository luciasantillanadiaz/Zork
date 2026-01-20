#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <windows.h>
#include "world.h"
#include "command.h"

using namespace std;

const string BOLD = "\033[1m";
const string RESET = "\033[0m";
const string RED = "\033[31m";

vector<string> ParseInput(string& input) {
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
    Command* commandSystem = world.GetCommandSystem();

    cout << RED << BOLD << " --- WELCOME TO MY ZORK! ---\n" << RESET;

    commands.push_back("look");

    while (true) {
        if (_kbhit()) {
            char key = _getch();

            if (key == '\b') {
                if (!input.empty()) {
                    input.pop_back();
                    cout << "\b \b";
                }
            }
            else if (key != '\r') {
                input += key;
                cout << key;
            }
            else { 
                cout << "\n";
                if (!input.empty()) {
                    commands = ParseInput(input);
                    input.clear();
                }
            }
        }

        if (!commands.empty()) {

            if (commands[0] == "quit") break;

            string action = commands[0];
            vector<string> args;
            if (commands.size() > 1) {
                args.assign(commands.begin() + 1, commands.end());
            }

            cout << "\n";

            commandSystem->ExecuteCommand(action, args);

            commands.clear();
            cout << "> ";
        }

        world.Update();

        Sleep(10);
    }

    cout << "\nThanks for playing!\n";
    return 0;
}