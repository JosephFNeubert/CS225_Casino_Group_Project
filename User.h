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
	User(string name);
	void changeUserName(string name, string fileName);
	string getUserName() const;
	void saveUserInfo(string fileName, bool nameRecorded);
	bool getUserInfo(string fileName, string inputName);
};
