#include "stdafx.h"
#include <array>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

bool yesNo();
char getChar();

enum CardRank {
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
	MAX_RANKS
};

enum CardSuit {
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES,
	MAX_SUITS
};

struct Card
{
	CardRank rank;
	CardSuit suit;
};
void printCard(const Card &temp) {

	switch (temp.rank)
	{
	case TWO:
		cout << "2";
		break;
	case THREE:
		cout << "3";
		break;
	case FOUR:
		cout << "4";
		break;
	case FIVE:
		cout << "5";
		break;
	case SIX:
		cout << "6";
		break;
	case SEVEN:
		cout << "7";
		break;
	case EIGHT:
		cout << "8";
		break;
	case NINE:
		cout << "9";
		break;
	case TEN:
		cout << "T";
		break;
	case JACK:
		cout << "J";
		break;
	case QUEEN:
		cout << "Q";
		break;
	case KING:
		cout << "K";
		break;
	case ACE:
		cout << "A";
		break;
	default:
		break;
	}

	switch (temp.suit)
	{
	case CLUBS:
		cout << "C\n";
		break;
	case DIAMONDS:
		cout << "D\n";
		break;
	case HEARTS:
		cout << "H\n";
		break;
	case SPADES:
		cout << "S\n";
		break;
	default:
		break;
	}
}

void printDeck(const array<Card, 52> &temp) {
	for (auto &mem : temp) {
		printCard(mem);
	}
	cout << "Finished printing!\n";
}

void swapCard(Card &a, Card &b) {
	swap(a, b);
}

void shaffleDeck(array<Card, 52> &temp) {
	mt19937 mersenne(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 52; i++) {
		swapCard(temp[mersenne() % 52], temp[mersenne() % 52]);
	}
	cout << "Shaffled!\n";
}

int getCardValue(const Card &temp) {
	/*printCard(temp);*/

	if (temp.rank <= NINE)
		return temp.rank + 2;
	else if (temp.rank <= KING)
		return 10;
	else
		return 11;
}

bool playBlackJack(const Card *CardPtr) {
	int scoreDealer{ getCardValue(*CardPtr++) };
	int scorePlayer{ getCardValue(*CardPtr++) };

	cout << ">>>>>>> The dealer's score is: " << scoreDealer << endl;

	while (1) {
		cout << ">>>>>>> Your score is: " << scorePlayer << endl;

		cout << "Enter Y to hit, N to stand!\n";

		bool userHit = yesNo();

		if (userHit) {
			scorePlayer += getCardValue(*CardPtr++);
			if (scorePlayer > 21) {
				cout << "Oops, your cards bust with score " << scorePlayer << "!\n";
				return 0;
			}
			scoreDealer += getCardValue(*CardPtr++);
			if (scoreDealer > 21) {
				cout << "Aha, you are lucky, dealer's cards bust with score " << scoreDealer << "!\n";
				return 1;
			}
		}
		else
		{
			int lp{ 1 };
			while (1) {
				if (scoreDealer > 16)
					break;
				cout << "Dealer score is less than 17, get another card. (NO. " << lp++ << ")" << endl;
				scoreDealer += getCardValue(*CardPtr++);
				if (scoreDealer > 21) {
					cout << "Aha, you are lucky, dealer's cards bust with score " << scoreDealer << "!\n";
					return 1;
				}
			}
			cout << "*******\t\tScores\t\t*******\n";
			cout << "*******\tYou " << scorePlayer << " VS " << scoreDealer << " Dealer\t*******" << endl;

			return (scoreDealer > scorePlayer) ? 0 : 1;
		}
	}
}

bool yesNo() {
	while (1) {
		char a{ getChar() };
		if (a == 'Y' || a == 'y')
			return 1;
		else if (a == 'n' || a == 'N')
			return 0;
		else
			cout << "Sorry, wrong input, please enter again! y / n.\n";
	}
}

char getChar() {
	char op;
	std::cin >> op;
	std::cin.ignore(32767, '\n'); // remove any extraneous input
	return op; // return it to the caller
}

int main() {
	array<Card, 52> allCard;

	int cardNum{ 0 };
	for (int suitCount = 0; suitCount < MAX_SUITS; suitCount++)
	{
		for (int rankCount = 0; rankCount < MAX_RANKS; rankCount++)
		{
			allCard[cardNum].suit = static_cast<CardSuit>(suitCount);
			allCard[cardNum].rank = static_cast<CardRank>(rankCount);
			cardNum++;
		}
	}

	cout << "Let's play the card game: BlackJack (or named Twenty-One)!\n";
	cout << "\n*******RULES******\n\n";
	cout << "* The dealer gets one card to start(in real life, the dealer gets two, but one is face down so it doesn¡¯t matter at this point).\n";
	cout << "* The player gets two cards to start.\n";
	cout << "* The player goes first.\n";
	cout << "* A player can repeatedly hit or stand.\n";
	cout << "* If the player stands, their turn is over.\n";
	cout << "* If the player hits, they get another card and the value of that card is added to their total score.\n";
	cout << "* An ace normally counts as a 1 or an 11 (whichever is better for the total score).For simplicity, we¡¯ll count it as an 11 here.\n";
	cout << "* If the player goes over a score of 21, they bust and lose immediately.\n";
	cout << "* The dealer goes after the player.\n";
	cout << "* The dealer repeatedly draws until they reach a score of 17 or more, at which point they stand.\n";
	cout << "* If the dealer goes over a score of 21, they bust and the player wins immediately.\n";
	cout << "* Otherwise, if the player has a higher score than the dealer, the player wins.Otherwise, the player loses.\n";
	cout << "\n*******RULES END*******\n\n";

	bool goOnPlay{ true };

	while (goOnPlay) {
		shaffleDeck(allCard);

		bool youWin = playBlackJack(&allCard[0]);

		if (youWin)
			cout << "*******\tCongrats! You win!\t*******\n\n";
		else {
			cout << "*******\tPity, you lose!\t*******\n\n";
		}

		cout << "\nWould you like play again? \n";
		goOnPlay = yesNo();
	}

	cout << "Thank you for playing!\n";

	return 0;
}

