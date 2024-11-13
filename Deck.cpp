#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include "Deck.h"
using namespace std;

Deck::Deck() {
    string suites[] = { "Hearts", "Diamonds", "Spades", "Clubs" };

    for (const string& suite : suites) {
        for (int rank = 1; rank <= 13; ++rank) {
            deck.push_back(Card(suite, rank));
        }
    }
}

Card Deck::getCard(int index) const {
    return deck[index];

}

void Deck::shuffleDeck() {
    srand(time(0));
    for (int i = deck.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(deck[i], deck[j]);
    }
}
