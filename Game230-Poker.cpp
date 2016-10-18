// Game230-Poker.cpp : Defines the entry point for the console application.
//
#include "GameManager.cpp"
#include "stdafx.h"
#include <string>
#include <stddef.h>
#include <iostream>
#include <array>
using namespace std; 


string strDeck = "deck";
string strExit = "exit";
string strSwap = "swap";
string strNone = "none";
string strAll = "all";
char magicChars[] = { 'a','b','c', 'd', 'e' };

bool isOneOf5MagicWords(string inp) {
	if (inp == "deck" || inp == "exit" || inp == "swap" || inp == "none" || inp == "deck" || inp == "all")
		return true;
	return false;
}

bool isMagicChars(string inp) { //danger, danger i feel it's not gonna work
	
	if (inp.length() > 5) return false;
	for each (char c in inp)
	{		
		for (int i = 0; i < sizeof(magicChars); i++) {
			if (magicChars[i] == c) break;
			if (i == sizeof(magicChars) - 1) return false;
		}
	}
	return true;
}
char validateCharInput() {
	string inp;
	for (;;) {
		if (cin >> inp &&inp.size() == 1 && isMagicChars(inp)) {
			//	if (isMagicChars(inp))
			
			break;
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		//return inp[0];
	}
	
	return (char)inp[0];
}
static string validateStringInput() {
	string inp;
  
	for (;;) {

		if(cin>>inp&& isMagicChars(inp) || isOneOf5MagicWords(inp))
			break;
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	
	return inp;
}

int validateIntInput(int min, int max) { //boundary for the input
	int input;
	for (;;) {

		if (cin >> input && input > min && input < max) {
			break;
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return input;
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
	void addFirst(Card* c) {
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
	void addLast(Card* c) {
		if (this->head == NULL) {
			addFirst(c);
			return;
		}
		Card* last = this->head;
	
		while (last->next != NULL)
			last = last->next;
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
		//delete c;
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
		//delete c;
		size--;
	}

	void removeCard(Card* c) {                                       //something is redundant here, but I've spent 2 hours on this function alone, it's late and I have no time to figure out how it works at all..
		if (head->suit == c->suit && head->value == c->value) {
			this->head = this->head->next;
			return;
		}
		Card* prev = this->head;
		while (true) {
			Card* cur = prev->next;
			
			if (cur->suit == c->suit && cur->value == c->value) {
				prev->next = cur->next;
				return;
			}
			prev = prev->next;
		}
	}
};
class Player {
public:
	int money;
	CardList* hand;

	Player() {
		money = 10;
		hand = new CardList;
	}
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
		return parseValue(c->value) + " of " + parseSuit(c->suit);
	}

};

class View {
public:
	static void printList(CardList* cl) {
		Card* c = cl->head;
//		cout<< Parser::parseCard(c)<<endl;
		int index = 0;
		while (c != NULL) {
			if (cl->size == 5) {
				cout << magicChars[index] << ": ";
				index++;
			}
			cout<< Parser::parseCard(c) << endl;
			c = c->next;
		}
	}

	static void printPlayerInfo(Player* p) {
		cout << endl << "Money: " << p->money << endl;
		cout << "Hand:" << endl;
		printList(p->hand);
		
	}
};


class GameManager {
public:
	CardList* deck;// = new CardList();
//	CardList* hand;// = new CardList();
	CardList* discard;// = new CardList();
	bool wannaPlay;
	Player* player;
	//	int playersMoney;
	GameManager() {
		//		playersMoney = 10;
		player = new Player();
		deck = new CardList();
		populateDeck();
		//		hand = new CardList();
		discard = new CardList();
		wannaPlay = true;
	}
	void drawNCards(int n) {
		for (int i = 0; i < n; i++) {
			//srand()
			int random = rand() % deck->size;

			//hand->addLast(deck->getItem(i));
			Card* c = deck->getItem(random);
			deck->removeCard(random);
			player->hand->addLast(c);

		}
	}

	//hardcode a bit
	void populateDeck() {
		for (int i = 2; i < 15; i++) {
			for (int j = 0; j < 4; j++) {
				//if(hand->head != NULL || !hand->contains(i,j))
				deck->addLast(i, j);
			}
		}
	}
	bool flush() {
		return false;
	}

	bool straight() {
		return false;
	}
	bool threeOfAKind() {
		return false;
	}
	bool street() {
		return false;
	}
	bool twoPairs() {
		return false;
	}
	bool pair() {
		return false;
	}
	int checkWinStreak() {
		if (flush()) {
			cout << "";
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

		if (twoPairs()) {
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


	Card* selectCardByChar(char ch) {
		//char ch = validateCharInput();
		switch (ch)
		{
		case 'a':
			return player->hand->getItem(0);
		case 'b':
			return player->hand->getItem(1);
		case 'c':
			return player->hand->getItem(2);
		case 'd':
			return player->hand->getItem(3);
		case 'e':
			return player->hand->getItem(4);
		default:
			break;
		}
	}
	void changeCards(string s) {
		/*
		for each (char ch in s)
		{
			transferCard(selectCardByChar(ch), di, player->hand);
			transferCard()
		}
		*/
		for each (char ch in magicChars) {
			if (!s.find(ch)) {
				transferCard(selectCardByChar(ch),  player->hand, discard);
				drawNCards(player->hand->size - s.size());
			}
		}
	}

	void swapCard() {
		for (;;) {
			cout << "Select a card to swap" << endl;
			
			char ch = validateCharInput();

			Card* selectedCard = selectCardByChar(ch);
			Card* tempC = new Card;
			cout << "Type in value (2 - 14)" << endl;
			//int inp = validateIntInput(2, 15);
			tempC->value = validateIntInput(1, 15);
			cout << "Type in suit (0 - 3)" << endl;
			tempC->suit = validateIntInput(-1, 4);
			
			if (transferCard(tempC, deck, player->hand) && transferCard(selectedCard, player->hand, discard) )
				return;
				
			else {
				cout << "wrong"<<endl;
			}
			
		}
		}
	bool transferCard(Card* c, CardList* from, CardList* to) { //from  to
		if (from->contains(c)) {
			from->removeCard(c);
			to->addLast(c);
			return true;
		}
		return false;
	}
	void react(string s) {
			if (s == strSwap) {
				swapCard();
			}
			else if (s == strExit)
				wannaPlay = false;
			else if (s == strDeck) {
				cout << endl << "The deck is" << endl;
				View::printList(deck);

			}
			else if (s == strNone) {
				//what?
			}
			else if (s == strAll) {
				//	changeAll();
			}
			
			else 
				changeCards(s);
					

					
				
			
			checkWinStreak();
		}
	void play()
		{
			//TODO create deck, fill deck
			drawNCards(5);
			while (wannaPlay) {

				View::printPlayerInfo(this->player);

				react(validateStringInput());

			}
			exit(0);
		}
};

	int main()
	{

		GameManager* gm = new GameManager();
		
		gm->play();
		string s = validateStringInput();
		return 0;
	}
