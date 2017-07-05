

#include <iostream>
#include <string>
#include "GameManager.h"
#include "Parser.h"
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

		if (cin >> inp&& isMagicChars(inp) || isOneOf5MagicWords(inp))
			break;
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "what was that?" << endl;
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
void printList(CardList* cl) {
	Card* c = cl->head;
	int index = 0;
	while (c != NULL) {
		if (cl->size == 5) {

			cout << magicChars[index] << ": ";
			index++;
		}
		cout << Parser::parseCard(c) << endl;
		c = c->next;
	}
}
void printPlayerInfo(Player* p, char magicChars[]) {
	cout << endl << "Money: " << p->money << endl;
	cout << "Hand:" << endl;
	printList(p->hand);

}
GameManager::GameManager() {

	player = new Player();
	deck = new CardList();
	populateDeck();

	discard = new CardList();
	wannaPlay = true;
}
GameManager::~GameManager() {
	delete player;
	delete deck;
	delete discard;
}
void GameManager::drawNCards(int n) {
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
void GameManager::populateDeck() {
	for (int i = 2; i < 15; i++) {
		for (int j = 0; j < 4; j++) {
			deck->addLast(i, j);
		}
	}
}

void GameManager::refillTheDeck() {
	CardList* temp;
	temp = deck;
	deck = discard;
	discard = temp;
	deck->orderCards();
}

bool GameManager::flush() {
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
bool GameManager::straightFlush() {
	if (flush() && straight())
		return true;
	return false;
}
bool GameManager::straight() {
	Card* prev = player->hand->head;
	Card* cur = prev->next;
	int streak = 0;
	while (cur != NULL) {
		if (cur->value - prev->value == 1)
			streak++;
		if (streak == 4)
			return true;
		prev = cur;
		cur = cur->next;
	}
	return false;
}
bool GameManager::threeOfAKind() {
	Card* cur = player->hand->head;
	Card* following = cur->next;
	while (cur != NULL &&cur->next != NULL&& cur->next->next != NULL) {
		if (cur->next->value == cur->value && cur->value == cur->next->next->value)
			return true;
		cur = cur->next;

	}
	return false;
}
bool GameManager::fourOfAKind() {
	Card* cur = player->hand->head;

	while (cur != NULL &&cur->next != NULL&& cur->next->next != NULL && cur->next->next->next != NULL) {
		if (cur->next->value == cur->value && cur->value == cur->next->next->value &&cur->next->next->value == cur->next->next->next->value)
			return true;
		cur = cur->next;


	}
	return false;
}
bool GameManager::fullHouse() {

	if (player->hand->getItem(0)->value == player->hand->getItem(1)->value && player->hand->getItem(2)->value == player->hand->getItem(3)->value && player->hand->getItem(3)->value == player->hand->getItem(4)->value)
		return true;
	if (player->hand->getItem(0)->value == player->hand->getItem(1)->value && player->hand->getItem(1)->value == player->hand->getItem(2)->value && player->hand->getItem(3)->value == player->hand->getItem(4)->value)
		return true;
	return false;
}

bool GameManager::royalFlush() {
	return (player->hand->head->value == 10 && flush());

}
bool GameManager::twoPairs() {
	Card* cur = player->hand->head;
	Card* following = cur->next;

	int streak = 0;
	while (cur != NULL && cur->next != NULL) {

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
bool GameManager::pair() {
	Card* cur = player->hand->head;
	Card* following = cur->next;
	while (cur != NULL && cur->next != NULL) {
		if (cur->next->value == cur->value && cur->value > 10) {
			return true;
		}
		cur = cur->next;
		//	while () {}
		//	cur = cur->next;
	}

	return false;
}
int GameManager::checkWinStreak() {
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
	cout << "you didn't win , sry" << endl;
	return 0;
}


Card* GameManager::selectCardByChar(char ch) {
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
void GameManager::changeCards(string s) {

	for (int i = 4; i >-1; i--) {
		if (s.find(magicChars[i]) == string::npos) {
			transferCard(selectCardByChar(magicChars[i]), player->hand, discard);
			drawNCards(1);
		}
	}
	player->hand->orderCards();
}

void GameManager::swapCard() {

	for (;;) {
		cout << "Select a card to swap" << endl;

		char ch = validateCharInput();

		Card* selectedCard = selectCardByChar(ch);

		cout << "Type in value (2 - 14)" << endl;
		int val = validateIntInput(1, 15);
		cout << "Type in suit (0 - 3)" << endl;

		int suit = validateIntInput(-1, 4);
		Card*c = deck->getItem(val, suit);
		if (c == NULL) {
			cout << "wrong" << endl;
			continue;
		}
		if (transferCard(deck->getItem(val, suit), deck, player->hand) && transferCard(selectedCard, player->hand, discard)) {
			player->hand->orderCards();
			return;
		}

		else {
			cout << "wrong" << endl;
		}
	}

}
bool GameManager::transferCard(Card* c, CardList* from, CardList* to) { //from  to
	if (from->contains(c)) {
		from->removeCard(c);
		to->addLast(c);
		return true;
	}
	return false;
}

void GameManager::react(string s) {
	if (s == strSwap) {
		swapCard();
		printList(player->hand);
	}
	else if (s == strExit) {
		wannaPlay = false;
		return;
	}
	else if (s == strNone) {
		changeCards("nlkhg");

		printList(player->hand);
	}
	else if (s == strAll) {
		printList(player->hand);
		return;
	}
	else {
		changeCards(s);
		printList(player->hand);
	}
	player->hand->orderCards();

}
void GameManager::clearHand() {
	Card*c = player->hand->head;
	Card* c2;
	while (c != NULL) {
		c2 = c->next;
		transferCard(c, player->hand, discard);
		c = c2;
	}
}
void GameManager::round() {

	printPlayerInfo(this->player, magicChars);
	string s = validateStringInput();
	if (s == "deck") {
		cout << endl << "The deck: " << endl;
		printList(deck);
		round();
	}
	else if (s == "swap") {
		swapCard();
		round();
	}
	else
		react(s);
}
void GameManager::play() {
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
			printList(deck);
		}
		getline(cin, s);
		if (s == "exit")wannaPlay = false;																										//why doesn't it work if used once..?
		if (s == "deck")printList(deck);
		clearHand();
	}
}
