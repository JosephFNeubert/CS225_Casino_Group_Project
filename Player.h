#pragma once
#include <iostream>
#include "Card.h"
#include "Deck.h"
using namespace std;

class Player {
private:
	vector<Card> hand;
	double balance;

public:
	Player(double money);
	void receiveCard(Deck& deck, int index);
	Card getCard(int index) const;
	void fold();
	void modifyBalance(double money);
	int getBalance() const;
	void savePlayerInfo();
};