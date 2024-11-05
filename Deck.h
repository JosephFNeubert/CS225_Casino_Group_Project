#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include <vector>

using namespace std;

class Deck : public Card {
    private:
        vector<Card> deck;

    public:
        Deck() {
            string suites[] = { "Hearts", "Diamonds", "Spades", "Clubs" };

            for (const string& suite : suites) {
                for (int rank = 1; rank <= 13; ++rank) {
                    deck.push_back(Card(suite, rank));
                }
            }
        }
        Card getCard(int index) const {
            return deck[index];
       
        }

        void shuffleDeck();
};