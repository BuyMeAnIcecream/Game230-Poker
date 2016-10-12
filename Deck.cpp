#include <stddef.h>
#include "Player.cpp"
class Deck {

public:	
	static CardList* createCardList() {
		CardList* cl = new CardList;
		cl->head = NULL;
		return cl;
	}
	//MOVE THIS SHIT TO CARDLIST!! IT'S HIS FUNCTIONALITY!!!! leave here only deck of 52 and so do with player, but 5 items only. and work, you retard, please.
	void addFirst(CardList* cl, int v, int s ) {
		Card* c = new Card;
		c->value = v;
		c->suit = s;
		c->next = cl->head;
		cl->head = c;
	}

	void addLast(CardList* cl, int v, int s) {
		if (cl->head == NULL) {
			addFirst(cl, v,s)
		}
	}
	
	//TODO
	void removeCard() {

	}
	//TODO
	/*
	void drawNCards(Player* pl, int n) {
		pl->hand.
	}*/
	
};
struct CardList {
	Card* head;
};
struct Card
{
public: 
	int value;
	int suit;
	Card* next;
};