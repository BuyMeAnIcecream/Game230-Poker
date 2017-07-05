#pragma once
#include <stddef.h>
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

	CardList();	
	~CardList();
	void addFirst(int v, int s);
	void addFirst(Card* c);
	void addLast(int v, int s);
	void addLast(Card* c);	
	void orderCards();
	Card* getItem(int index);
	Card* getItem(int v, int s);
	bool contains(Card* c);
	bool contains(int v, int s);
	void removeFirst();
	void removeCard(int index);	
	void deleteList();
	Card* removeCard(Card* c);
};