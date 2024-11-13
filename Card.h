#pragma once
#include <iostream>
using namespace std;

class Card {
private:
    string suite;
    int rank;

public:
    int index;

    Card(string suite, int rank);
    Card();
    friend ostream& operator<<(ostream& os, const Card& card) {
        string rankStr;
        if (card.rank == 1) {
            rankStr = "Ace";
            os << rankStr << " of " << card.suite;
        }
        else if (card.rank == 11) {
            rankStr = "Jack";
            os << rankStr << " of " << card.suite;
        }
        else if (card.rank == 12) {
            rankStr = "Queen";
            os << rankStr << " of " << card.suite;
        }
        else if (card.rank == 13) {
            rankStr = "King";
            os << rankStr << " of " << card.suite;
        }
        else {
            os << card.rank << " of " << card.suite;
        }
        return os;
    }
    string getSuite() const;
    int getRank() const;
};
