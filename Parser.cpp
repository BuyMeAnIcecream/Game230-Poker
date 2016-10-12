#include <string>
using namespace std;

class Parser {
public:
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
	}
};