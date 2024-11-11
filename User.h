#pragma once
#include <iostream>
#include "Player.h"
using namespace std;

class User : public Player {
private:
	string name;

public:
	User(double money, string name);
	void savePlayerInfo();
	void receivePlayerInfo();
};
