
#include <iostream>
#include <string>
#include "controller.h"

using namespace std;

int main(int argc, char *argv[]) {
	/*if ()
	(argc > 1) ? Controller c{argv[1]} : Controller c;*/

	Controller c;

	char race;
	cout << "Welcome to CC3K!" << endl;
	cout << "Please choose a race:" << endl;
	cout << "s(Shade), d(Drow), v(Vampire), t(Troll) or g(Goblin)" << endl;
	cout << endl;

	while (cin >> race) {
		if (race == 's' || race == 'd' || race == 'v' || race == 'g' || race == 't') {
			cout << endl;
			cout << "Loading the game..." << endl;
			cout << endl;
			c.init(race);
			break;
		}
		cout << "Please choose a race:" << endl;
		cout << "s(Shade), d(Drow), v(Vampire), t(Troll) or g(Goblin)" << endl;
	}

	cout << c;
	string cmd1 = "";

	cout << endl;
	cout << "Please enter a command: " << endl;

	while (cin >> cmd1) {
		cout << endl;
		if (cmd1 == "no" || cmd1 == "so" || cmd1 == "ea" || cmd1 == "we" || cmd1 == "ne" || cmd1 == "nw" || cmd1 == "se" || cmd1 == "sw") {
			c.makeMove("move", cmd1);
		}
		else if (cmd1 == "u" || cmd1 == "a") {
			string cmd2 = "";
			cin >> cmd2;
			if (cmd2 == "no" || cmd2 == "so" || cmd2 == "ea" || cmd2 == "we" || cmd2 == "ne" || cmd2 == "nw" || cmd2 == "se" || cmd2 == "sw") {
				c.makeMove(cmd1, cmd2);
			}
		}
		else if (cmd1 == "f") {
			cout << "Freezing the enemies..." << endl;
			c.freeze();
		}
		else if (cmd1 == "r") {
			cout << "Restarting the game..." << endl;
			c.restart();
			c.init(race);
		}
		else if (cmd1 == "q") {
			cout << "Quitting the game..." << endl;
			c.quit();
			break;
		}
		else {
			cout << "Please enter a valid command." << endl;
			continue;
		}
		cout << c;

		cout << endl;
		cout << "Please enter a command: " << endl;
	}
	return 0;
}
