/*
 PROGRAMMER:       	Mark Eskander
 Program Description:
  Card game which assigns different point amounts to
  cards. Deck is shuffled. 4 players play at a time.
  Player with 2 of clubs starts first the next game.
*/
#include "CardClass.h"
#include "cardtype.h"
#include <iostream>
#include <iomanip>
using namespace std;

// global constant
const int cardLimit = 13;

// function prototypes
void dealCards(CardType p1[], CardType p2[], CardType p3[], CardType p4[], CardClass gameDeck);
void sortCards(CardType p[]);
void printCards(CardType p1[], CardType p2[], CardType p3[], CardType p4[], string club);
void displaySuit(int x);
void displayValue(int x);
void displayPoints(int x);
void displayHeader(int x);

int n() {
  CardClass gameDeck = CardClass(); // create object (deck of cards) to start game

  gameDeck.shuffleCards(); // shuffle deck

  string club = gameDeck.clubHolder(); // find 2 of club holder

  // declare 4 players as 1D arrays of CardType
  CardType p1[cardLimit], p2[cardLimit], p3[cardLimit], p4[cardLimit];

  // deal 1 card to 4 players 13 times = 52 cards dealt
  dealCards(p1, p2, p3, p4, gameDeck);
  
  // sort each player's hand
  sortCards(p1);
  sortCards(p2);
  sortCards(p3);
  sortCards(p4);

  // print each player's hand and 2 of club holder
  printCards(p1, p2, p3, p4, club);

  return 0;
}

void sortCards(CardType p[]) 
{
  int index;     // start point
  cardSuitType minSuitVal; // start min value string
  int maxCardVal; // value of card (2-14)

  // nested loop to sort a player's hand
  for (int i = 0; i < cardLimit - 1; i++) 
  {
    index = i;           // set start value
    minSuitVal = p[i].suits; // assign min value to first card's suit

    for (int j = i + 1; j < cardLimit; j++) // start from next card in player's hand and compare
    {
      if (p[j].suits < minSuitVal) // replace cards as needed
      {
        minSuitVal = p[j].suits;
        index = j;
      }
    }
    swap(p[index], p[i]); // swap the two cards, putting the lowest found card
                          // at the top most position
  }
  // same loop as above, but to sort by card's value
  for (int i = 0; i < cardLimit - 1; i++) 
  {
    index = i;
    maxCardVal = p[i].value;
    minSuitVal = p[i].suits;
      
    for (int j = i + 1; j < cardLimit; j++)
    {
      // compare values of cards with same suits
      if (p[j].suits == minSuitVal && p[j].value > maxCardVal)
      {
        maxCardVal = p[j].value;
        index = j;
      }
    }
    swap(p[index], p[i]);
  }
}

void printCards(CardType p1[], CardType p2[], CardType p3[], CardType p4[], string club) 
{
  for (int x = 0; x < 4; x++) 
  {
    displayHeader(x);
    for (int y = 0; y < cardLimit; y++) 
    {
      if (x == 0) // print player 1's hand
      {
        displaySuit(p1[y].suits);
        displayValue(p1[y].value);
        displayPoints(p1[y].points);
      } 
      else if (x == 1) // print player 2's hand
      {
        displaySuit(p2[y].suits);
        displayValue(p2[y].value);
        displayPoints(p2[y].points);
      } 
      else if (x == 2) // print player 3's hand
      {
        displaySuit(p3[y].suits); 
        displayValue(p3[y].value);
        displayPoints(p3[y].points);
      } 
      else // print player 4's hand
      {
        displaySuit(p4[y].suits); 
        displayValue(p4[y].value);
        displayPoints(p4[y].points);
      }
    }
    cout << endl;
  }
  cout << club << " will start the game next round." << endl;
}

void dealCards(CardType p1[], CardType p2[], CardType p3[], CardType p4[], CardClass gameDeck)
{
  // deal one player one card 13 times
  for (int x = 0; x < cardLimit; x++) 
  {
    p1[x] = gameDeck.dealCard();
    p2[x] = gameDeck.dealCard();
    p3[x] = gameDeck.dealCard();
    p4[x] = gameDeck.dealCard();
  }
}

void displaySuit(int x)
{
  // print the suit of each card
  switch (x)
    {
      case 0:
        cout << setw(7) << "Diamond";
        break;
      case 1:
        cout << setw(7) << "Heart";
        break;
      case 2:
        cout << setw(7) << "Spade";
        break;
      case 3:
        cout << setw(7) << "Club";
        break;
    }
}

void displayValue(int x)
{
  if (x < 11) // number cards
  {
    cout << setw(10) << x;
  }
  else // face cards and Ace
  {
    switch (x)
      {
        case 11:
          cout << setw(10) << "J";
          break;
        case 12:
          cout << setw(10) << "Q";
          break;
        case 13:
          cout << setw(10) << "K";
          break;
        case 14:
          cout << setw(10) << "A";
          break;
      }
  }
}

void displayPoints(int x)
{
  cout << setw(14) << x << endl;
}

void displayHeader(int x)
{
  switch (x) 
    {
    case 0: // header for player 1
      cout << setw(20) << "PLAYER 1" << endl;
      cout << "SUIT" << setw(15) << "VALUE" << setw(15) << "POINTS" << endl;
      break;

    case 1: // header for player 2
      cout << setw(20) << "PLAYER 2" << endl;
      cout << "SUIT" << setw(15) << "VALUE" << setw(15) << "POINTS" << endl;
      break;

    case 2: // header for player 3
      cout << setw(20) << "PLAYER 3" << endl;
      cout << "SUIT" << setw(15) << "VALUE" << setw(15) << "POINTS" << endl;
      break;

    case 3: // header for player 4
      cout << setw(20) << "PLAYER 4" << endl;
      cout << "SUIT" << setw(15) << "VALUE" << setw(15) << "POINTS" << endl;
      break;
    }
}