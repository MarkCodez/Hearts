/*Mark Eskander
- program used to play card game "hearts"
- 4 players allowed. player with least amount
- of points wins.
*/
#include "CardClass.h"
#include "PlayerClass.h"
#include "mytype.h"

#include "time.h"
#include <iomanip>
#include <iostream>
using namespace std;

// global constant
const int numPlayers = 4;

// function prototypes
void dealCards(PlayerClass players[], CardClass gameDeck);
void sortCards(PlayerClass players[]);
int isFirstLead(PlayerClass players[]);
void playRound(PlayerClass players[], CardType table[], int &lead, int x,
               cardSuitType &leadSuit);
void displayHeader();
void displayGameLead(int lead);
void showUser(PlayerClass players[]);
int findHighest(CardType table[], cardSuitType suit);
void displayMoves(CardType table[], int lead);
void displayValue(int x);
void displaySuit(int x);
void displayPoints(int x);
void addScores(CardType table[], PlayerClass players[], int lead);
CardType promptUser1(PlayerClass players[]);
CardType promptUser2(PlayerClass players[], cardSuitType suit);
void scoreBoard(PlayerClass players[]);
void revealWinner(PlayerClass players[]);
void printCards(PlayerClass players[]);

int main()
{
  CardClass gameDeck = CardClass(); // creating object (deck of 52 cards)
  PlayerClass players[numPlayers];  // array of 4 objects (players)
  CardType table[numPlayers];       // table that holds 4 cards played by players

  srand(time(NULL));
  gameDeck.shuffleCards();      // shuffling the deck of cards
  dealCards(players, gameDeck); // deal cards to players
  sortCards(players);           // sort cards in each player's hand

  int lead =
      isFirstLead(players); // find who starts the game (2 of club holder)
  cardSuitType leadSuit;    // determine what suit is the leading suit

  displayHeader();

  for (int x = 0; x < MAX_PLAYER_CARDS; x++)
  {
    displayGameLead(lead);

    cout << endl;
    cout << "Round " << x + 1 << endl;

    playRound(players, table, lead, x, leadSuit); // one round of card game

    displayMoves(table, lead);
    cout << endl;

    lead = (findHighest(table, leadSuit) + lead) % 4; // find next round leader
    cout << endl;

    addScores(table, players, lead);
    cout << endl;

    scoreBoard(players);
    cout << endl;
  }

  revealWinner(players);

  return 0;
}

void dealCards(PlayerClass players[], CardClass gameDeck)
{
  // CardType temp;

  // deal one card 13 times
  for (int x = 0; x < MAX_PLAYER_CARDS; x++)
  {
    for (int i = 0; i < numPlayers;
         i++) // deal one card to 4 players, one player at a time
    {
      players[i].AddCard(gameDeck.dealCard());
    }
  }
}

void sortCards(PlayerClass players[])
{
  // sort 4 players' hands, 1 at a time
  for (int i = 0; i < numPlayers; i++)
  {
    players[i].Sort();
  }
}

int isFirstLead(PlayerClass players[])
{
  int i;
  // check 4 players' hand until 2 of club holder is found
  for (i = 0; i < numPlayers; i++)
  {
    if (players[i].IsFirstLead()) // return which player has 2 of club
    {
      break;
    }
  }
  return i;
}

void playRound(PlayerClass players[], CardType table[], int &lead, int x,
               cardSuitType &leadSuit)
{
  int i;

  // display user cards
  showUser(players);

  for (i = 0; i < numPlayers; i++)
  {
    if (x == 0) // frst round of game
    {
      if (i == 0) // first play of first round
      {
        table[i] = players[(lead + i) % 4].Play2Club();
        leadSuit = table[i].suits;
      }
      else if ((lead + i) % 4 == 0 &&
               i != 0) // first round for user but not first play
      {
        table[i] = promptUser2(players, leadSuit);
      }
      else // first round for computer but not first play
      {
        table[i] = players[(lead + i) % 4].FollowOneCard(leadSuit);
      }
    }
    else // if round is not 0
    {
      if ((lead + i) % 4 == 0 && i == 0) // user and first play of round
      {
        table[i] = promptUser1(players);
        leadSuit = table[i].suits;
      }
      else if ((lead + i) % 4 == 0 &&
               i != 0) // user and not first play of round
      {
        table[i] = promptUser2(players, leadSuit);
      }
      else // computers
      {
        if (i == 0) // first play of round
        {
          table[i] = players[(lead + i) % 4].StartOneHand();
          leadSuit = table[i].suits;
        }
        else // not first play of round
        {
          table[i] = players[(lead + i) % 4].FollowOneCard(leadSuit);
        }
      }
    }
  }
}

void displayHeader()
{
  // display header for game name
  cout << "*********************************" << endl;
  cout << setw(20) << "HEARTS" << endl;
  cout << "*********************************" << endl;
}

void displayGameLead(int lead)
{
  // print which player will start the game
  switch (lead)
  {
  case 0:
    cout << "User is the lead" << endl;
    break;
  case 1:
    cout << "Computer " << lead << " is the lead" << endl;
    break;
  case 2:
    cout << "Computer " << lead << " is the lead" << endl;
    break;
  case 3:
    cout << "Computer " << lead << " is the lead" << endl;
    break;
  }
}

void showUser(PlayerClass players[])
{
  cout << "Your cards: " << endl;
  cout << "#" << setw(10) << "SUIT" << setw(12) << "VALUE" << setw(12)
       << "POINTS" << endl;
  players[0].DisplayCards(); // show user's cards

  cout << endl;
}

int findHighest(CardType table[], cardSuitType suit)
{
  // set default values to compare
  int maxVal = 0;
  int index = 0;

  // search in table for highest value played of leading suit
  for (int x = 0; x < numPlayers; x++)
  {
    // if greater value of leading suit found then save index
    if (table[x].suits == suit && table[x].value > maxVal)
    {
      maxVal = table[x].value;
      index = x;
    }
  }
  return index; // return the position of the highest value found
}

void displayMoves(CardType table[], int lead)
{
  for (int x = 0; x < numPlayers; x++)
  {
    if ((lead + x) % 4 == 0)
    {
      cout << "User plays: ";
    }
    else
    {
      cout << "Computer " << (lead + x) % 4 << " plays: ";
    }
    displayValue(table[x].value);
    displaySuit(table[x].suits);
    displayPoints(table[x].points);
  }
}

void displayValue(int x)
{
  if (x > 1 && x < 11) // number cards
  {
    cout << x << " of ";
  }
  else // face cards and Ace
  {
    switch (x)
    {
    case 11:
      cout << "J "
           << "of ";
      break;
    case 12:
      cout << "Q "
           << "of ";
      break;
    case 13:
      cout << "K "
           << "of ";
      break;
    case 14:
      cout << "A "
           << "of ";
      break;
    }
  }
}

void displaySuit(int x)
{
  // print the suit of each card
  switch (x)
  {
  case 0:
    cout << setw(13) << left << "Diamond";
    break;
  case 1:
    cout << setw(13) << left << "Heart";
    break;
  case 2:
    cout << setw(13) << left << "Spade";
    break;
  case 3:
    cout << setw(13) << left << "Club";
    break;
  }
}

void displayPoints(int x)
{
  cout << setw(7) << right << "(" << x << ")" << endl;
}

void addScores(CardType table[], PlayerClass players[], int lead)
{
  int playerScore;
  int sum = 0;
  for (int a = 0; a < numPlayers; a++)
  {
    sum += table[a].points;
  }
  switch (lead)
  {
  case 0:
    cout << "-----User gets " << sum << " points-----" << endl;
    players[lead].AddScore(sum);
    playerScore = players[lead].GetScore();
    break;
  case 1:
    cout << "-----Computer " << lead << " gets " << sum << " points-----"
         << endl;
    players[lead].AddScore(sum);
    playerScore = players[lead].GetScore();
    break;
  case 2:
    cout << "-----Computer " << lead << " gets " << sum << " points-----"
         << endl;
    players[lead].AddScore(sum);
    playerScore = players[lead].GetScore();
    break;
  case 3:
    cout << "-----Computer " << lead << " gets " << sum << " points-----"
         << endl;
    players[lead].AddScore(sum);
    playerScore = players[lead].GetScore();
    break;
  }
}

void printCards(PlayerClass players[])
{
  for (int x = 0; x < numPlayers; x++)
  {
    cout << "Your cards: " << x << endl;
    cout << "#" << setw(10) << "SUIT" << setw(12) << "VALUE" << setw(12)
         << "POINTS" << endl;
    for (int i = 0; i < 1; i++)
    {
      players[x].DisplayCards(); // show user's cards
    }
    cout << endl;
  }
}

CardType promptUser1(PlayerClass players[])
{
  // prompt user for card to play
  int userChoice;
  cout << "Enter a card to be played: ";
  cin >> userChoice;
  cout << endl;
  // return selected card
  return players[0].PlaySelectedCard(userChoice);
}

CardType promptUser2(PlayerClass players[], cardSuitType suit)
{
  // prompt user for choice to play
  int userChoice;
  cout << "Leading suit is ";

  // print the suit of each card
  switch (suit)
  {
  case 0:
    cout << "Diamond" << endl;
    break;
  case 1:
    cout << "Heart" << endl;
    break;
  case 2:
    cout << "Spade" << endl;
    break;
  case 3:
    cout << "Club" << endl;
    break;
  }

  cout << "Enter a card to be played: ";
  cin >> userChoice;
  cout << endl;

  // validate card
  while (!(players[0].IsValidChoice(suit, userChoice)))
  {
    cout << "Invalid choice. Try again: ";
    cin >> userChoice;
    cout << endl;
  }
  // return correct card
  return players[0].PlaySelectedCard(userChoice);
}

void scoreBoard(PlayerClass players[])
{
  cout << "----- Score Board -----" << endl;
  for (int x = 0; x < numPlayers; x++)
  {
    if (x == 0)
    {
      cout << "User: " << players[x].GetScore() << endl;
    }
    else
    {
      cout << "Computer " << x << ": " << players[x].GetScore() << endl;
    }
  }
}

void revealWinner(PlayerClass players[])
{
  int minVal = players[0].GetScore();
  int index = 0;

  for (int x = 1; x < numPlayers; x++)
  {
    if (players[x].GetScore() < minVal)
    {
      minVal = players[x].GetScore();
      index = x;
    }
  }

  if (index == 0)
  {
    cout << "You are the winner with " << players[index].GetScore()
         << " points!" << endl;
  }
  else
  {
    cout << "Computer " << index % 4 << " is the winner with "
         << players[index].GetScore() << " points!" << endl;
  }
}