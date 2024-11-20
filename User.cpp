#include "User.h"
using namespace std;

User::User(string name) : Player() {
	this->name = name;
}

void User::changeUserName(string name, string fileName) {
	bool validName = true;
	string line;
	string tempName;
	double tempBalance;
	ifstream file(fileName);
	if (!file) {
		cout << "Error opening the file. Please retype the file name." << endl;
		return;
	}
	else {
		while (getline(file, line)) {
			istringstream stream(line);
			if (stream >> tempName >> tempBalance) {
				if (tempName == name) {
					validName = false;
					file.seekg(0);
					break;
				}
			}
		}

		string newName;
		bool flag = false;
		while (!validName) {
			cout << "That name already exists. Please select another name." << endl;
			flag = true;
			cin >> newName;
			while (getline(file, line)) {
				istringstream stream(line);
				if (stream >> tempName >> tempBalance) {
					if (tempName == newName) {
						file.seekg(0);
						cin.clear();
						cin.ignore(INT_MAX, '\n');
						flag = false;
						break;
					}
				}
			}
			if (flag) {
				validName = true;
			}
		}

		if (flag) {
			this->name = newName;
		}
		else {
			this->name = name;
		}
		cout << "Success! Welcome to the casino " << this->name << "." << endl;
	}
	file.close();
}

string User::getUserName() const {
	return name;
}

void User::saveUserInfo(string fileName, bool nameRecorded) {
	if (nameRecorded) {
		ifstream fileIn(fileName);
		if (!fileIn) {
			cout << "Error opening the file. Please retype the file name." << endl;
			return;
		}
		else {
			string tempSavedData = "";
			string tempString;
			string tempName;
			double tempBalance;
			while (getline(fileIn, tempString)) {
				istringstream stream(tempString);
				if (stream >> tempName >> tempBalance) {
					if (tempName == name) {
						tempBalance = getBalance();
					}
					tempSavedData += tempName;
					tempSavedData += " ";
					tempSavedData += to_string(tempBalance);
					tempSavedData += "\n";
				}
			}
			tempSavedData.pop_back();
			fileIn.close();
			ofstream fileOut(fileName);
			fileOut << tempSavedData;
			fileOut.close();
		}
	}
	else {
		ofstream fileOut(fileName, ios::app);
		fileOut << "\n" << name << " " << getBalance();
		fileOut.close();
	}
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
