#include "Player.h"
using namespace std;

Player::Player(double money) : balance(money) {}

void Player::receiveCard(Deck& deck, int index) {
	Card newCard = deck.getCard(index);
	hand.push_back(newCard);
	deck.index++;
}

Card Player::getCard(int index) const {
	return hand.at(index);
}

void Player::setBalance(double money) {
	balance = money;
}

void Player::modifyBalance(double money, int operation) {
	try {
		if (operation == 1) {
			balance += money;
		}
		else if (operation == 2) {
			balance -= money;
			if (balance < 0) {
				balance = 0;
			}
		}
		else {
			throw(operation);
		}
	}
	catch (int x) {
		cout << "ERROR: Operation number " << x << " is invalid.\nPlease input either '1' or '2' for addition or subtraction respectively." << endl;
		exit(0);
	}
}

int Player::getBalance() const {
	return balance;
}

int Player::calculateHandValue() const {
	int total = 0;
	int aceCount = 0;


	for (const Card& card : hand) {
		int rank = card.getRank();
		if (rank == 1) {  // Ace
			total += 11;
			++aceCount;
		}
		else if (rank >= 11 && rank <= 13) {
			total += 10;
		}
		else {
			total += rank;
		}
	}


	while (total > 21 && aceCount > 0) {
		total -= 10;
		--aceCount;
	}

	return total;
}
void Player::clearHand() {
	hand.clear();
}

size_t Player::getHandSize() {
	return hand.size();
}
