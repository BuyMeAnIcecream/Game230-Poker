// Game230-Poker.cpp : Defines the entry point for the console application.
//
#include "GameManager.cpp"
#include "stdafx.h"
#include <string>
#include <stddef.h>
#include <iostream>
using namespace std;


class Deck {

public:
	static CardList* createCardList() {
		CardList* cl = new CardList;
		cl->head = NULL;
		return cl;
	}
	//MOVE THIS SHIT TO CARDLIST!! IT'S HIS FUNCTIONALITY!!!! leave here only deck of 52 and so do with player, but 5 items only. and work, you retard, please.
	void addFirst(CardList* cl, int v, int s) {
		Card* c = new Card;
		c->value = v;
		c->suit = s;
		c->next = cl->head;
		cl->head = c;
	}

	void addLast(CardList* cl, int v, int s) {
		if (cl->head == NULL) {
			addFirst(cl, v, s);
			return;
		}
		Card* last = cl->head;
		while (last->next != NULL)
			last = last->next;

		Card* c = new Card;
		c->suit = s;
		c->value = v;
		c->next = NULL;
		last->next = c;
	}

	Card* getItem(CardList* cl, int index) {
		Card* c = cl->head;
		while (index > 0) {
			c = c->next;
			--index;
		}
		return c;
	}

	//TODO
	void removeFirst(CardList* cl) {
		if (cl->head == NULL) 
			return;
		Card* c = cl->head;
		cl->head = c->next;
		delete c;

	}
	void removeCard(CardList* cl,int index) {
		if (index == 0) {
			removeFirst(cl);
			return;
		}
		Card* prev = cl->head;
		while (index > 1) {
			prev = prev->next;
			--index;
		}
		Card* c = prev->next;
		prev->next = c->next;
		delete c;
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
class Parser {
private:
	

	static string parseValue(int value) {
		switch (value) {
		case 2: return "2";
		case 3: return "3";
		case 4: return "4";
		case 5: return "5";
		case 6: return "6";
		case 7: return "7";
		case 8: return "8";
		case 9: return "9";
		case 10: return "10";
		case 11: return "Jack";
		case 12: return "Queen";
		case 13: return "King";
		case 14: return "Ace";
		default: return "you fed me some bullshit";
		}
	}


	static string parseSuit(int value) {
		switch (value) {
		case 0: return "Spades";
		case 1: return "Hearts";
		case 2: return "Clubs";
		case 3: return "Diamonds";
		default: return "you fed me some bullshit";
		}
	};
public:
	static string parseCard(Card* c) {
		//string parsed = 
		return parseValue(c->suit) + " of " + parseSuit(c->value);
	}

};

class View {
public:
	static void printList(CardList* cl) {
		Card* c = cl->head;
//		cout<< Parser::parseCard(c)<<endl;
		while (c != NULL) {
			cout<< Parser::parseCard(c) << endl;
			c = c->next;
		}
	}
};
class GameManager {
public:
	Deck deck;

	GameManager() {

	}
};

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
int main()
{
	GameManager* gm = new GameManager();
    return 0;
}
