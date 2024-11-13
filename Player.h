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

public:
	Player(double money = 200);
	void receiveCard(Deck& deck, int index);
	Card getCard(int index) const;
	void setBalance(double money);
	void modifyBalance(double money, int operation);
	int getBalance() const;
	int calculateHandValue() const;
	void clearHand();
	size_t getHandSize();
};
