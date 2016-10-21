// Game230-Poker.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#include "GameManager.cpp"
#include "stdafx.h"
#include <string>
#include <stddef.h>
#include <iostream>
#include <array>
#include <time.h> 
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
		deleteList();
		size = 0;
		head = NULL;
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

	void orderCards() {
		int sizee = this->size;
		int i = 0;
		Card* lastSwapped = NULL;
		while (sizee--)
		{
			Card
				*current = head,
				*prev = NULL, // We are at the beginnig, so there is no previous node.
				*currentSwapped = NULL;

			while (current->next != lastSwapped) // We have at least one node (size > 0) so `current` itself is not NULL.
			{
				Card *after = current->next;
				if (current->value > after->value|| current->value ==after->value && current->suit > after->suit)// || current->suit > after->suit)
				{
					//swap the items
					current->next = after->next;
					after->next = current;
					if (prev == NULL) // we are at the beginning
						head = after;
					else
						prev->next = after;

					prev = after;
					currentSwapped = current;
				}
				else
				{
					prev = current;
					current = current->next;
				}
			}
			if (currentSwapped == NULL)
				break; // No swapping occured. The items are sorted.
			else
				lastSwapped = currentSwapped;
		}
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

	void deleteList() {

		Card* c = head;
		while (c != NULL) {
			Card* c2 = c;
			c = c->next;
			delete c2;
		}
		//delete this;
		c = NULL;
		head = NULL;
	}
	Card* removeCard(Card* c) {                                       //something is redundant here, but I've spent 2 hours on this function alone, it's late and I have no time to figure out how it works at all..
		if (head->suit == c->suit && head->value == c->value) {
			this->head = this->head->next;
			size--;
			return head;
		}
		Card* prev = this->head;
		while (prev!=NULL) {
			Card* cur = prev->next;
			
			if (cur->suit == c->suit && cur->value == c->value) {
				prev->next = cur->next;
				size--;
				return cur;
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
	~Player() {
		delete hand;
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
		case 0: return "Clubs";
		case 1: return "Diamonds";
		case 2: return "Hearts";
		case 3: return "Spades";
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
	~GameManager() {
		delete player;
		delete deck;
		delete discard;
	}
	void drawNCards(int n) {
		if (n == 0)
			return;
		for (int i = 0; i < n; i++) {
			if (deck->size < 1)
				refillTheDeck();
				 
			int random = rand() % deck->size;
			Card* c = deck->getItem(random);

			transferCard(c, deck, player->hand);
		}
	}
	
	//hardcode a bit
	void populateDeck() {
		for (int i = 2; i < 15; i++) {
			for (int j = 0; j < 4; j++) {
				deck->addLast(i, j);
			}
		}
	}
	
	void refillTheDeck() {
		CardList* temp; 
		temp = deck;
		deck = discard;
		discard = temp;
		deck->orderCards();
	}

	bool flush() {
		Card* prev = player->hand->head;
		Card* cur = prev->next;
		int streak = 0;
		while (cur != NULL) {
			if (prev->suit == cur->suit)
				streak++;
			if (streak == 4)
				return true;
			prev = cur;
			cur = cur->next;
		}
		return false;
	}
	bool straightFlush() {
		if (flush() && straight())
			return true;
		return false;
	}
	bool straight() {
		Card* prev = player->hand->head;
		Card* cur = prev->next;
		int streak = 0;
		while (cur != NULL) {
			if ( cur->value - prev->value == 1)
				streak++;
			if (streak == 4)
				return true;
			prev = cur;
			cur = cur->next;
		}
		return false;
	}
	bool threeOfAKind() {
		Card* cur = player->hand->head;
		Card* following = cur->next;
		while (cur != NULL &&cur->next != NULL&& cur->next->next!=NULL ) {
			if (cur->next->value == cur->value && cur->value== cur->next->next->value)
				return true;
			cur = cur->next;
			
		}
		return false;
	}
	bool fourOfAKind() {
		Card* cur = player->hand->head;
		//Card* following = cur->next;
		while (cur != NULL &&cur->next != NULL&& cur->next->next != NULL && cur->next->next->next != NULL) {
			if (cur->next->value == cur->value && cur->value == cur->next->next->value &&cur->next->next->value == cur->next->next->next->value)
				return true;
			cur = cur->next;
			//following = cur->next;

		}
		return false;
	}
	bool fullHouse() {
		
		if (player->hand->getItem(0)->value == player->hand->getItem(1)->value && player->hand->getItem(2)->value == player->hand->getItem(3)->value && player->hand->getItem(3)->value == player->hand->getItem(4)->value)
			return true;
		if (player->hand->getItem(0)->value == player->hand->getItem(1)->value && player->hand->getItem(1)->value == player->hand->getItem(2)->value && player->hand->getItem(3)->value == player->hand->getItem(4)->value)
			return true;
		return false;
	}

	bool royalFlush() {
		return (player->hand->head->value == 10 && flush());
			
	}
	bool twoPairs() {
		Card* cur = player->hand->head;
		Card* following = cur->next;
		
		int streak = 0;
		while (cur != NULL && cur->next!=NULL) {
			
			if (cur->next->value == cur->value) {
				
				streak++;
				if (streak == 2)
					return true;
				cur = cur->next->next;
				continue;
			}
			
		
			cur = cur->next;
		}
		return false;
	}
	bool pair() {
		Card* cur =  player->hand->head;
		Card* following = cur->next;
		while (cur != NULL && cur->next!=NULL) {
			if (cur->next->value == cur->value && cur->value > 10){
				return true;
				}
			cur = cur->next;
		//	while () {}
		//	cur = cur->next;
		}
			
		return false;
	}
	int checkWinStreak() {
		if (royalFlush()) {
			cout << "congrats, you won 800 with royal flush" << endl;
			return 800;
		}
		if (straightFlush()) {
			cout << "congrats, you won 50 with straight flush" << endl;
			return 50;
		}
		if (fourOfAKind()) {
			cout << "congrats, you won 25 with four of a kind" << endl;
			return 25;
		}
		if (fullHouse()) {
			cout << "congrats, you won 9 with full house" << endl;
			return 9;
		}
		if (flush()) {
			cout << "congrats, you won 6 withflush" << endl;
			return 6;
		}
		if (straight()) {
			cout << "congrats, you won 4 with straight" << endl;
			return 4;
		}
		if (threeOfAKind()) {
			cout << "congrats, you won 3 with three of a kind" << endl;
			return 3;
		}
		if (twoPairs()) {
			cout << "congrats, you won 2 with two pairs" << endl;
			return 2;
		}
		if (pair()) {
			cout << "congrats, you won 1 with pair" << endl;
			return 1;
		}
		cout << "you didn't win , sry"<<endl; 
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
		
		//for each (char ch in magicChars) {
		for(int i = 4; i >-1; i--){
		if (s.find(magicChars[i])==string::npos) {
			//cout << magicChars[i];
				transferCard(selectCardByChar(magicChars[i]),  player->hand, discard);
				drawNCards(1);
			}
			//drawNCards(player->hand->size - s.size());
		}
		player->hand->orderCards();
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

			if (transferCard(tempC, deck, player->hand) && transferCard(selectedCard, player->hand, discard)) {
				player->hand->orderCards();

				return;
		}
				
			else {
				cout << "wrong"<<endl;
			}
		}
		
	}
	bool transferCard(Card* c, CardList* from, CardList* to) { //from  to
		if (from->contains(c)) {
			from->removeCard(c);
			//from->removeCard(from->getItem(c));
			to->addLast(c);
			return true;
		}
		return false;
	}
	
	void react(string s) {
		//View::printPlayerInfo(player);
		if (s == strSwap) {
			swapCard();
			View::printList(player->hand);
		}
		else if (s == strExit) {
			wannaPlay = false;
			return;
		}
	//	else if (s == strDeck) {
			
	//		react(validateStringInput());
	//	}
		else if (s == strNone) {
			changeCards("nlkhg");
			
			View::printList(player->hand);
		}
		else if (s == strAll) {
			View::printList(player->hand);
			return;
		}
		else {
			changeCards(s);
			View::printList(player->hand);
		}
		player->hand->orderCards();
		
	}
	void clearHand() {
		Card*c = player->hand->head;
		Card* c2;
		while (c!=NULL) {
			c2 = c->next;
			transferCard(c, player->hand, discard);
			c = c2;
		}
	}
	void round() {
		
		View::printPlayerInfo(this->player);
		string s = validateStringInput();
		if (s == "deck" ) {
			cout << endl << "The deck: " << endl;
			View::printList(deck);
			round();
		}
		else if (s == "swap") {
			swapCard();
			round();
		}
		else 
			react(s);
		//react(validateStringInput());
	//	if (s != "all" || s != "none" || s != "swap" || s != "exit")
	//		react(validateStringInput());
	}
	void play() {
		cout << "you had  " << player->money << " to waste. " << endl;
		while (wannaPlay&&player->money >1) {
			player->money--;
			drawNCards(5);
			player->hand->orderCards();
			round();
			if (!wannaPlay)return;
			player->money += checkWinStreak();
			cout << "any button for next round" << endl;
			
			string s;
			getline(cin, s);
			if (s == "exit") { wannaPlay = false; continue; }
			if (s == "deck") {
				cout << endl << "The deck: " << endl;
				View::printList(deck);
			}
			getline(cin, s);
			if (s == "exit")wannaPlay = false;																										//why doesn't it work if used once..?
			if (s == "deck")View::printList(deck);
			clearHand();
		}
	}

};
	int main()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
			_CRTDBG_LEAK_CHECK_DF);
		GameManager* gm = new GameManager();
		
		srand(time(NULL));
		gm->play();
		delete gm;
		return 0;
	}
