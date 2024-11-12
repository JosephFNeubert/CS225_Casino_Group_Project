#include "Player.h"
using namespace std;

Player::Player(double money) : balance(money) {}

void Player::receiveCard(Deck& deck, int index) {
	Card newCard = deck.getCard(index);
	hand.push_back(newCard);
}

Card Player::getCard(int index) const {
	return hand.at(index);
}

void Player::fold() {
	balance -= bet;
	cout << "You have folded. Your bet of $" << bet << " has been lost." << endl;
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
			throw("Invalid operation.");
		}
	}
	catch (string x) {
		cout << x << "\nPlease input either '1' or '2' for addition or subtraction respectively." << endl;
	}
}

int Player::getBalance() const {
	return balance;
}

int Player::calculateHandValue() const {
        int total = 0;
        int aceCount = 0;

        // Calculate the initial total, treating aces as 11
        for (const Card& card : hand) {
            int rank = card.getRank();
            if (rank == 1) {  // Ace
                total += 11;
                ++aceCount;
            } else if (rank >= 11 && rank <= 13) {  // Face cards (Jack, Queen, King)
                total += 10;
            } else {  // Numeric cards
                total += rank;
            }
        }

        // Adjust for aces if total is over 21
        while (total > 21 && aceCount > 0) {
            total -= 10;  // Count one ace as 1 instead of 11
            --aceCount;
        }

        return total;
    }

