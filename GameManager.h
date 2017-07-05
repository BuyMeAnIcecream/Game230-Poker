#pragma once
#include <string>
#include "CardList.h"
#include "Player.h"
using namespace std;
static char magicChars[] = { 'a','b','c', 'd', 'e' };
static string strDeck = "deck";
static string strExit = "exit";
static string strSwap = "swap";
static string strNone = "none";
static string strAll = "all";


class GameManager {
public:
	CardList* deck;
	CardList* discard;
	bool wannaPlay;
	Player* player;
	GameManager();
	~GameManager();
	void drawNCards(int n);
	void populateDeck();
	void refillTheDeck();
	bool flush();
	bool straightFlush();
	bool straight();
	bool threeOfAKind();
	bool fourOfAKind();
	bool fullHouse();
	bool royalFlush();
	bool twoPairs();
	bool pair();
	int checkWinStreak();
	Card* selectCardByChar(char ch);
	void changeCards(string s);
	void swapCard();
	bool transferCard(Card* c, CardList* from, CardList* to);
	void react(string s);
	void clearHand();
	void round();
	void play();

};