#include "User.h"
using namespace std;

User::User(string name) : Player() {
	this->name = name;
}

void User::changeUserName(string name, string fileName) {
	bool validName = true;
	string line;
	string tempName;
	ifstream file(fileName);
	if (!file) {
		cout << "Error opening the file. Please retype the file name." << endl;
		return;
	}
	else {
		while (getline(file, line)) {
			istringstream stream(line);
			if (stream >> tempName) {
				if (tempName == name) {
					validName = false;
					file.seekg(0);
				}
			}
		}

		string newName;
		while (!validName) {
			cout << "That name already exists. Please select another name." << endl;
			cin >> newName;
			while (getline(file, line)) {
				istringstream stream(line);
				if (stream >> tempName) {
					if (tempName == newName) {
						file.seekg(0);
						continue;
					}
				}
			}
		}

		if (validName) {
			this->name = name;
		}
		else {
			this->name = newName;
		}
	}
}

string User::getUserName() const {
	return name;
}

void User::saveUserInfo(string fileName) {
	ofstream file(fileName, ios::app);
	file << name << " " << getBalance() << "\n";
	file.close();
}

bool User::getUserInfo(string fileName, string inputName) {
	bool userFound = false;
	string tempName;
	double tempBalance;
	string line;
	ifstream file(fileName);
	if (!file) {
		cout << "Error opening the file. Please retype the file name." << endl;
		return false;
	}
	else {
		while (getline(file, line)) {
			istringstream stream(line);
			if (stream >> tempName >> tempBalance) {
				if (tempName == inputName) {
					this->name = inputName;
					setBalance(tempBalance);
					userFound = true;
				}
			}
		}

		file.close();
		if (userFound) {
			cout << "Success! Welcome back to the casino " << inputName << "." << endl;
			return true;
		}
		else {
			cout << "User not found." << endl;
			return false;
		}
	}
}
