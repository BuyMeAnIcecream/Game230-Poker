// Game230-Poker.cpp : Defines the entry point for the console application.
//
#include "GameManager.cpp"
#include "stdafx.h"
#include <string>
#include <stddef.h>
#include <iostream>
using namespace std; 


string strDeck = "deck";
string strExit = "exit";
string strSwap = "swap";
string strNone = "none";
string strAll = "all";

static string validateInput() {
//	string inp = cin.getline();
	//TODO validation
	/*
	for (;;) {
	inp = console.getline();
		if (inp == "a" || inp == "b" || inp == "c" || inp == "d" || inp == "e" ||
			inp == "deck" || inp == "exit" || inp == "swap" || inp == "none" || inp == "deck" || inp == "all") {
			return inp;
		}
	}
	*/
	return "nope";
}
struct Card
{
public:
	int value;
	int suit;
	Card* next;
};
class CardList {
public:
	Card* head;
	int size;
	CardList() {
		head = NULL;
		size = 0;
	}
	~CardList() {
		//TODO
	}
	void addFirst(int v, int s) {
		Card* c = new Card;
		c->value = v;
		c->suit = s;
		c->next = this->head;
		this->head = c;
		size++;
	}

	void addLast(int v, int s) {
		if (this->head == NULL) {
			addFirst(v, s);
			return;
		}
		Card* last = this->head;
		while (last->next != NULL)
			last = last->next;

		Card* c = new Card;
		c->suit = s;
		c->value = v;
		c->next = NULL;
		last->next = c;
		size++;
	}

	Card* getItem(int index) {
		Card* c = this->head;
		while (index > 0) {
			c = c->next;
			--index; 
		}
		return c;
	}
	
	

	bool contains(Card* c) {
		for(int i = 0; i<size; i++)
		{
			if (getItem(i)->suit == c->suit &&getItem(i)->value == c->value)
				return true;
		}
		return false;
	}

	bool contains(int v, int s) {
		for (int i = 0; i<size; i++)
		{
			if (getItem(i)->suit == s &&getItem(i)->value == v)
				return true;
		}
		return false;
	}
	//TODO
	void removeFirst() {
		if (this->head == NULL)
			return;
		Card* c = this->head;
		this->head = c->next;
		delete c;
		size--;

	}
	void removeCard(int index) {
		if (index == 0) {
			removeFirst();
			return;
		}
		Card* prev = this->head;
		while (index > 1) {
			prev = prev->next;
			--index;
		}
		Card* c = prev->next;
		prev->next = c->next;
		delete c;
		size--;
	}
};
/*
class Deck {

public:
	static CardList* createCardList() {
		CardList* cl = new CardList;
		cl->head = NULL;
		return cl;
	};
};
*/
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
		return parseValue(c->value) + " of " + parseSuit(c->suit);
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
	CardList* deck = new CardList();
	CardList* hand = new CardList();

	bool wannaPlay;
	
	void drawNCards(int n) {
		for (int i = 0; i < n; i++) {
			//srand()
			int random = rand() % max + min;
		}
	}
	
	//hardcode a bit
	void populateDeck() {
		for (int i = 2; i <15 ; i++) {
			for (int j = 0; j < 4; j++) {
				if(hand->head != NULL || !hand->contains(i,j))
					deck->addLast(i, j);
			}
		}
	}

	int checkWinStreak() {
		if (flush()) {
			cout<<"";
			return 5;
		}

		if (straight()) {
			cout << "";
			return 4;
		}

		if (threeOfAKind()) {
			cout << "";
			return 3;
		}
		
		if (twoPair()) {
			cout << "";
			return 2;
		}

		if (pair()) {
			cout << "";
			return 1;

		}
		
		//TODO 0 if none 1 if double, 2 if triple, so on...
		return 0;
	}
	void react(string s) {
		if (s == strSwap) {
			//TODO	
		}
		else if (s == strExit)
			wannaPlay = false;
		else if (s == strDeck)
			View::printList(deck);
		else if (s == strNone) {
			//what?
		}
		else if (s == strAll) {
			//	changeAll();
		}
		checkWinStreak();


	}
	void play()
	{
		//TODO create deck, fill deck
		wannaPlay = true;
		while (wannaPlay) {
			react(validateInput());
		}
		exit(0);
	}


		

	
	
};
/*
class Player {
public:
	int money;
	CardList* hand;

	Player() {
//		hand = Deck::createCardList();

	}

	void drawNCards(int n) {

	}

};
*/
int main()
{
	CardList* cl = new CardList();
	//cl->addLast(2, 3);
	//cl->addLast(14, 3);
	//cl->removeCard(1);


	
	GameManager* gm = new GameManager();
	gm->populateDeck();
	View::printList(gm->deck);
    return 0;
}
