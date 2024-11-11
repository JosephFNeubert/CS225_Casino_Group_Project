#pragma once
#include <iostream>
#include "Player.h"

class Bot : public Player {
public:
	Bot();
	void playBlackjack();
	void fold();
};
