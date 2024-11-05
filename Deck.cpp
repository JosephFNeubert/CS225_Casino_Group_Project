#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include "Deck.h"

using namespace std;

    void Deck::shuffleDeck() {
        srand(time(0));
        for (int i = deck.size() - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(deck[i], deck[j]);
        }
    }