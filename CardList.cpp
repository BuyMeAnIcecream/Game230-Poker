#include "CardList.h"
using namespace std;


CardList::CardList() {
	head = NULL;
	size = 0;
}
CardList::~CardList() {
	deleteList();
	size = 0;
	head = NULL;
	//TODO
}

void CardList::addFirst(int v, int s) {
	Card* c = new Card;
	c->value = v;
	c->suit = s;
	c->next = this->head;
	this->head = c;
	size++;
}

void CardList::addFirst(Card* c) {
	c->next = this->head;
	this->head = c;
	size++;
}

void CardList::addLast(int v, int s) {
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
void CardList::addLast(Card* c) {
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

void CardList::orderCards() {
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
			if (current->value > after->value || current->value == after->value && current->suit > after->suit)// || current->suit > after->suit)
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
Card* CardList::getItem(int index) {
	Card* c = this->head;
	while (index > 0) {
		c = c->next;
		--index;
	}
	return c;
}

Card* CardList::getItem(int v, int s) {
	Card* c = this->head;
	while (c != NULL) {
		if (c->value == v && s == c->suit)
			return c;
		c = c->next;
	}
	return NULL;
}


bool CardList::contains(Card* c) {
	for (int i = 0; i<size; i++)
	{
		if (getItem(i)->suit == c->suit &&getItem(i)->value == c->value)
			return true;
	}
	return false;
}

bool CardList::contains(int v, int s) {
	for (int i = 0; i<size; i++)
	{
		if (getItem(i)->suit == s &&getItem(i)->value == v)
			return true;
	}
	return false;
}
//TODO
void CardList::removeFirst() {
	if (this->head == NULL)
		return;
	Card* c = this->head;
	this->head = c->next;
	//delete c;
	size--;

}
void CardList::removeCard(int index) {
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

void CardList::deleteList() {

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
Card* CardList::removeCard(Card* c) {                                       //something is redundant here, but I've spent 2 hours on this function alone, it's late and I have no time to figure out how it works at all..
	if (head->suit == c->suit && head->value == c->value) {
		this->head = this->head->next;
		size--;
		return head;
	}
	Card* prev = this->head;
	while (prev != NULL) {
		Card* cur = prev->next;

		if (cur->suit == c->suit && cur->value == c->value) {
			prev->next = cur->next;
			size--;
			return cur;
		}
		prev = prev->next;
	}

}