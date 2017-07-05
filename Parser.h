#pragma once
#include <string>
#include "CardList.h"
using namespace std;

class Parser {
private:
	static string parseValue(int value);
	static string parseSuit(int value);
public:
	static string parseCard(Card* c);

};
