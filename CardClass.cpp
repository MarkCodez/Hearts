// implementation file for Card class
#include "CardClass.h"
#include "mytype.h"
#include "time.h"
#include <iostream>
#include <random>
#include <string>
using namespace std;

CardClass::CardClass() 
{
  for (int i = 0; i < 4; i++) // loop to assign suits to cards
  {
    for (int j = 2; j < 15; j++) // loop to assign values to cards 2-14
    {
      deckCards[gameDeckCount].suits = static_cast<cardSuitType>(i);
      deckCards[gameDeckCount].value = j;

      if (deckCards[gameDeckCount].suits == DIAMOND) // enter if suit is diamond, assign corresponding points
      {
        if (j == 11) // if card is Jack
        {
          deckCards[gameDeckCount].points = -75;
        } 
        else // if card is not Jack
        {
          deckCards[gameDeckCount].points = -7;
        }
      } 
      else if (deckCards[gameDeckCount].suits == HEART) // enter if suit is heart, assign corresponding points
      {
        if ((j <= 9)) // if card is not 10, J, Q, K, or A
        {
          deckCards[gameDeckCount].points = 5;
        } 
        else // if card is 10, J, Q, K, or A
        {
          deckCards[gameDeckCount].points = 15;
        }
      } 
      else if (deckCards[gameDeckCount].suits == SPADE) // enter if suit is spade, assign corresponding points
      {
        if (!(j == 12)) // if card is not the Queen
        {
          deckCards[gameDeckCount].points = 1;
        } 
        else // if card is the Queen
        {
          deckCards[gameDeckCount].points = 100;
        }
      } 
      else // enter if suit is club, assign corresponding points
      {
        deckCards[gameDeckCount].points = -2;
      }
      gameDeckCount++;
    }
  }
}

void CardClass::shuffleCards() 
{
  int x, y;
  CardType temp;

  // switching 2 cards 100 times
  for (int i = 0; i < 100; i++) 
  {
    // assign x and y random num between 0-51
    x = rand() % 52;
    y = rand() % 52;
    // keep copy of first card as temp to make the switch
    temp = deckCards[x];
    deckCards[x] = deckCards[y];
    deckCards[y] = temp;
  }
}

CardType CardClass::dealCard() 
{
  CardType temp;
  temp = deckCards[0]; // keep copy of top card on deck to be dealt

  for (int i = 0; i < gameDeckCount; i++) 
  {
    deckCards[i] = deckCards[i + 1]; // move each card down in the deck one position
  }
  gameDeckCount--; // decrement num of cards in the deck by 1
  return temp; // return top card of deck
}

int CardClass::getSize() const 
{
  return gameDeckCount; // number of cards remaining in the deck
}

bool CardClass::isEmpty() const 
{
  if (!gameDeckCount) // if not 0 (empty)
  {
    return false;
  } 
  else // if card count is 0 (has cards remaining)
  {
    return true;
  }
}

string CardClass::clubHolder() const 
{
  bool found = false;
  int index = 0;
  while (!found) // keep searching until 2 of clubs is found
  {
    // if 2 of clubs found exit loop
    if (deckCards[index].value == 2 && deckCards[index].suits == CLUB) 
    {
      break;
    }
    index++;
  }
  // mod index to get a number 0-3
  int club = index % 4;

  // return which player has 2 of club based on mod
  string player;
  switch (club) 
  {
  case 0:
    player = "Player 1";
    break;
  case 1:
    player = "Player 2";
    break;
  case 2:
    player = "Player 3";
    break;
  case 3:
    player = "Player 4";
    break;
  }
  return player;
}
