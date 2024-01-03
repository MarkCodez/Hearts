// header file for the card class
#ifndef Card_Class
#define Card_Class

#include "mytype.h"
#include <iostream>
using namespace std;

// global constant
const int SIZE = 52;

class CardClass 
{
private:
  CardType deckCards[SIZE];
  int gameDeckCount = 0;

public:
  CardClass(); // default constructor

  void shuffleCards(); // to randomize cards

  CardType dealCard(); // to deal 4 people 13 cards each, one card at a time

  int getSize() const; // returns the number of cards in the deck

  bool isEmpty() const; // returns true/false if the deck has remaining cards

  string clubHolder() const; // returns which player has the 2 of clubs
};

#endif