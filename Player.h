#pragma once
#include "CardList.h"

class Player {
public:
	int money;
	CardList* hand;
	Player();
	~Player();
};