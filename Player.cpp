
#include "Deck.cpp"
class Player {
public:
	int money;
	CardList* hand;

	Player() {
		hand = Deck::createCardList();

	}

	void drawNCards(int n) {
		
	}
	
};