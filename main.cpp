#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cctype>

using namespace std;

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

    cout << "Welcome to Zork!\n" << endl;

    while (1) {
        cout << "> ";

        getline(cin, input);
        if (input.empty()) continue;       

        commands = parseInput(input);
        if (commands.empty()) continue;

        if (commands[0] == "quit") break;
        else cout << "Command not recognized." << endl;
    }

    cout << "\nThanks for playing!\n";
    return 0;
}