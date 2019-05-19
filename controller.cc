#include <iostream>
#include "controller.h"
#include <memory>

using namespace std;

Controller::Controller(string fileName): m{make_unique<Map>(fileName)}, fileName{fileName} {}

void Controller::init(char pc) {
	m->init(pc);
}

void Controller::makeMove(string cmd1, string cmd2) {
	if (cmd1 == "move")	m->move(cmd2);
	else if (cmd1 == "a") m->attack(cmd2);
	else if (cmd1 == "u") m->drinkPotion(cmd2);
}

void Controller::freeze() {
	m->freeze();
}

void Controller::restart() {
	m.reset();
	m = make_unique<Map>(this->fileName);
}

void Controller::quit() {
	m.reset();
}

std::ostream & operator<<(std::ostream & out, const Controller & c)
{
	out << *(c.m);
	return out;
}
