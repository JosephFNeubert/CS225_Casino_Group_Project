#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Player.h"
using namespace std;

class User : public Player {
private:
	string name;

public:
	User(string name, string fileName);
	void saveUserInfo(string fileName);
	void getUserInfo(string fileName, string inputName);
};
