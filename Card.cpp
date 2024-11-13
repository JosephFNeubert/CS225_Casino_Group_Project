#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Card.h"
using namespace std;

Card::Card(string suite, int rank) : suite(suite), rank(rank) {}
Card::Card() {
    suite = suite;
    rank = rank;
}

string Card::getSuite() const { return suite; }

int Card::getRank() const { return rank; }
