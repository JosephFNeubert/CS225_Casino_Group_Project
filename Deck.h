#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include <vector>
using namespace std;

class Deck : public Card {
public:
    vector<Card> deck;
    int index;

    Deck();
    Card getCard(int index) const;
    void shuffleDeck();
};
