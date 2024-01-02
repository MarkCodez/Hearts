/* define the enum type for card suits here
// also define the card struct type here
#ifndef cardtype
#define cardtype

#include <iostream>
#include <string>
using namespace std;

enum cardSuitType { DIAMOND, HEART, SPADE, CLUB };

struct CardType;

struct CardType 
{
  cardSuitType suits;
  int value = -1;
  int points;
};

#endif*/