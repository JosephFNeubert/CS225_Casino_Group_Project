//Main
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include "Deck.h"
#include <vector>
#include "Player.h"


using namespace std;

void playBlackJack(Deck& deck, Player& User);

int main() {
	srand(time(0));
	Deck cardDeck;
    Player user;
    playBlackJack(cardDeck, user);

	return 0;
}

void playBlackJack(Deck& deck, Player& User) {
    string decision;
    bool Playing = true;
    Player Dealer(10000000);
    int playerSum;
    int dealerSum;

    while (Playing) {
        playerSum = 0;
        dealerSum = 0;
        deck.shuffleDeck();
        User.clearHand();
        Dealer.clearHand();


        User.receiveCard(deck, deck.index);
        Dealer.receiveCard(deck, deck.index);
        User.receiveCard(deck, deck.index);
        Dealer.receiveCard(deck, deck.index);

        cout << "You receive:\n";
        for (int i = 0; i < User.getHandSize(); ++i) {
            cout << User.getCard(i) << endl;
        }

        playerSum = User.calculateHandValue();
        cout << "Your hand value: " << playerSum << endl;

        cout << "Dealer shows: " << Dealer.getCard(0) << endl;


        bool playerTurn = true;
        while (playerTurn) {
            cout << "Hit or Stay? ";
            cin >> decision;

            if (decision == "Hit" || decision == "hit") {
                User.receiveCard(deck, deck.index);
                cout << "You receive: " << User.getCard(User.getHandSize() - 1) << endl;

                playerSum = User.calculateHandValue();
                cout << "Your hand value: " << playerSum << endl;

                if (playerSum > 21) {
                    cout << "Bust! You lose." << endl;
                    playerTurn = false;
                    Playing = false;
                }
                if (playerSum = 21) {
		    Playing = false;
                    cout << "You Win!"
                }
            }
            else if (decision == "Stay" || decision == "stay") {
                playerTurn = false;
            }
            else {
                cout << "Invalid input. Please enter 'Hit' or 'Stay'." << endl;
            }
        }

        if (playerSum <= 21) {
            dealerSum = Dealer.calculateHandValue();
            cout << "Dealer's hand: ";
            for (int i = 0; i < Dealer.getHandSize(); ++i) {
                cout << Dealer.getCard(i) << " ";
            }
            cout << "\nDealer's hand value: " << dealerSum << endl;

            while (dealerSum < 17) {
                cout << "Dealer hits." << endl;
                Dealer.receiveCard(deck, deck.index);
                dealerSum = Dealer.calculateHandValue();

                cout << "Dealer's hand value: " << dealerSum << endl;
                if (dealerSum > 21) {
                    cout << "Dealer busts! You win!" << endl;
                    Playing = false;
                }
            }

            if (dealerSum <= 21 && playerSum <= 21) {
                if (playerSum > dealerSum) {
                    cout << "You win!" << endl;
                }
                else if (playerSum < dealerSum) {
                    cout << "Dealer wins!" << endl;
                }
                else {
                    cout << "It's a tie!" << endl;
                }
            }
        }

        cout << "Do you want to play again? (yes or no) ";
        string replay;
        cin >> replay;
        if (replay == "yes" || replay == "Yes") {
            Playing = true;
        }
        else {
            Playing = false;
        }
    }
}
