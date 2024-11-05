#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include <Vector>

using namespace std;

void playBlackJack(Deck& deck, Player& User) {
	string decision;
	bool Playing = true;
	Player Dealer(10000000);
	int playerSum;
	int dealerSum;
	int index;
	while (Playing) {
		playerSum = 0;
		dealerSum = 0;
		deck.index = 0;
		int i;
		deck.shuffleDeck();
		User.receiveCard(deck, deck.index);
		Dealer.receiveCard(deck, deck.index);
		User.receiveCard(deck, deck.index);
		Dealer.receiveCard(deck, deck.index);
		cout << "You recieve :"
		for (i = 0; i < User.Hand.size(); ) {
			cout << User.getCard(i) << endl;
			playerSum += User.getCard(i).getrank();
		}


	}
	
}
