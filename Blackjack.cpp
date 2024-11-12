#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include <iostream>
#include <vector>

using namespace std;

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
        Dealer.receiveCard(deck);
        User.receiveCard(deck);
        Dealer.receiveCard(deck);

        cout << "You receive:\n";
        for (int i = 0; i < User.hand.size(); ++i) {
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
                User.receiveCard(deck.dealCard());
                cout << "You receive: " << User.getCard(User.getHandSize() - 1) << endl;

                playerSum = User.calculateHandValue();
                cout << "Your hand value: " << playerSum << endl;

                if (playerSum > 21) {
                    cout << "Bust! You lose." << endl;
                    playerTurn = false;
                    Playing = false;
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
                Dealer.receiveCard(deck.dealCard());
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
        if (replay != "yes" && replay != "Yes") {
            Playing = false;
        }
    }
}
