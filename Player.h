#pragma once
#include <iostream>
#include <cstdlib>
#include "Card.h"
#include "Deck.h"
using namespace std;

class Player {
private:
	vector<Card> hand;
	double balance;
	double bet;

public:
	Player(double money = 200);
	void receiveCard(Deck& deck, int index);
	Card getCard(int index) const;
	void fold();
	void modifyBalance(double money, int operation);
	int getBalance() const;
};
