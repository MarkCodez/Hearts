#include "mytype.h"
#include "CardClass.h"
#ifndef PlayerClass_H
#define PlayerClass_H

// global constant
const int MAX_PLAYER_CARDS = 13;

class PlayerClass 
{
  private:
  CardType hand[MAX_PLAYER_CARDS]; //  the set of cards held by the player
  int cardCount; // keeps record of number of cards player has
  int score; // keeps score for the player

public:
  // default constructor
  // post-condition: count is assigned 0, score is assigned 0
  PlayerClass();

  // Adds one card to the player's hand.
  // Cards are always added to one’s hand by adding it at the end of all cards
  // already in one’s hand. pre-condition: player has less than 13 cards
  // post-condition: player has one more card in the hand count is increased by
  // 1
  void AddCard(CardType card);

  // prints out the current cards the player has
  // pre-condition:  The player has some cards on hand
  // post-condition: the player’s cards are displayed.
  void DisplayCards() const;

  // select to play the first card that has the suit supplied from the client
  // program if no card can be found that has the suit supplied by the client
  // program, the first card from the hand is played pre-condition: there are >=
  // 1 cards in hand post-condition: a card is returned, count is decremented by
  // 1
  CardType FollowOneCard(cardSuitType suit);

  // plays the first card of a round. The top card in the deck is selected
  // pre-condition: there are >= 1 card in the hand
  // post-condition: one card is played/returned, count is decremented by 1
  CardType StartOneHand();

  // Checks to see if the player should lead the
  // first round in the game, e.g., check whether the player has 2 of club
  // pre-condition: the hand is full (have 13 cards)
  // post-condition: if this player has 2 of club, true is returned, otherwise,
  // return false.
  bool IsFirstLead() const;

  // play card 2 of club
  // pre-condition: the player has 2 of club on hand
  // post-condition: 2 of club is played/returned. Cards following “2 of Club”
  // is shifted up
  // number of cards remaining on hand is decremented
  // by 1
  CardType Play2Club();

  // The current score of the player is returned
  int GetScore() const;

  // the points from the current round is added to the current player's score
  // pre-condition: a point value is sent in from client
  // post-condition: the player's score is increased by the points from the
  // client program
  void AddScore(int x);

  // Return the number of cards the player has
  // pre-condition: none
  // post-condition:   the number of cards currently in the player’s hand is
  // returned
  int GetCount() const;

  // sorts the cards by suit
  // pre-condition: there are >=1 cards in hand
  // post-condition: the cards are sorted by suit
  void Sort();

  // plays the card selected by user
  // pre-condition:  the card number selected by the user is supplied
  // post-condition: the card corresponding to the user choice is
  // played/returned the number of cards in player's hand is decremented by 1. If
  // this card is in the middle of one’s hand, all cards following that card
  // are shifted as a result of removing the card
  CardType PlaySelectedCard(int choice);

  // Checks to see if the card the user chooses is a valid choice, e.g., whether
  // it matches the leading suit on that hand, if he has any. pre-condition: the
  // player's choice and the leading suit are supplied post-condition: returns
  // true if (1) user has cards of leading suit and the choice card is of that
  // suit, or (2) user does not have card of leading suit
  // and returns false otherwise
  bool IsValidChoice(cardSuitType, int) const;
};
#endif
