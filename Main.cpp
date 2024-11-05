//Main
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Card.h"
#include "Deck.h"
#include <vector>

using namespace std;
int main() {
	srand(time(0));
	Deck deck;
	deck.shuffleDeck();
	int x = rand() % 52 + 1;
	int i = 0;
	for (i = 0; i < 52; ++i) {
		cout << deck.getCard(i) << endl;
	}
	return 0;
}