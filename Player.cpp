
#include "Player.h"

Player::Player() {
	money = 10;
	hand = new CardList;
}
Player::~Player() {
	delete hand;
}