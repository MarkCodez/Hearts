// implementation file for Player class
#include "CardClass.h"
#include "PlayerClass.h"
#include "mytype.h"
#include "time.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
using namespace std;

PlayerClass::PlayerClass()
{
    // default constructor to initialize values
    cardCount = 0;
    score = 0;
}

void PlayerClass::AddCard(CardType card)
{
    // enter if player hand is not full
    if (cardCount < 13)
    {
        hand[cardCount] = card;//place card in correct position of player hand
        
        cardCount ++; // increment cards in hand by 1
    }
}

void PlayerClass::DisplayCards() const
{
    // iterate through hand to display current cards
    for (int i = 0; i < cardCount; i++)
    {
        cout << setw(5) << left << i + 1;
        switch (hand[i].suits)
        {
          case 0:
            cout << setw(10) << left << "DIAMOND";
            break;
          case 1:
            cout << setw(10) << left << "HEART";
            break;
          case 2:
            cout << setw(10) << left << "SPADE";
            break;
          case 3:
            cout << setw(10) << left << "CLUB";
            break;
        }

        if (hand[i].value < 11) // number cards
        {
            cout << setw(7) << right << hand[i].value;
        }
        else // face cards and Ace
        {
            switch (hand[i].value)
            {
                case 11:
                cout << setw(7) << right << "J";
                break;
                case 12:
                cout << setw(7) << right << "Q";
                break;
                case 13:
                cout << setw(7) << right << "K";
                break;
                case 14:
                cout << setw(7) << right << "A";
                break;
            }
        }
        cout << setw(12) << hand[i].points << endl;
    }
}

CardType PlayerClass::FollowOneCard(cardSuitType suit)
{
    CardType temp; 
    // ensure the deck has atleast one card before entering
    if (cardCount >= 1 && cardCount < MAX_PLAYER_CARDS)
    {
        for (int i = 0; i < cardCount - 1; i++) // iterate through deck
        {
            if (hand[i].suits == suit) // enter if matching suit is found
            {
                temp = hand[i];
                for (int j = i; j < cardCount - 1; j++) // shift deck accordingly
                {
                    hand[j] = hand[j+1];
                }
                cardCount --; // decrement cards in hand
                return temp; // return correct card w matching suit
            }
        }
        // do if matching suit not found
        temp = hand[0];
        for (int x = 0; x < cardCount - 1; x++) // shift deck accordingly
        {
            hand[x] = hand[x+1];
        }
        cardCount --; 
        return temp; // return first card of hand
    }
}

CardType PlayerClass::StartOneHand()
{
    CardType temp;

    if (cardCount >= 1) // enter only if player has atleast one card
    {
        temp = hand[0];
        // shift cards up in the player's hand accordingly
        for (int i = 0; i < cardCount - 1; i++)
        {
            hand[i] = hand[i + 1];
        }
        cardCount --; // decrement cards in hand by 1
        return temp; // return the first card in player's hand
    }
}

bool PlayerClass::IsFirstLead() const
{
    if (cardCount == 13) // enter if player's hand is full
    {
        bool found = false;
        int index = 0;
        while (!found && index < cardCount) // keep searching until 2 of clubs is found
        {
            // if 2 of clubs found, exit loop
            if (hand[index].value == 2 && hand[index].suits == CLUB) 
            {
              found = true;
              break;
            }
            index++;
        }
        return found; // return true or false
    }
}

CardType PlayerClass::Play2Club()
{
    CardType temp;
    bool found = false;
    int index = 0;

    while (!found && index < cardCount) // keep searching until 2 of clubs is found
    {
        // if 2 of clubs found exit loop
        if (hand[index].value == 2 && hand[index].suits == CLUB) 
        {
            temp = hand[index];
            break;
        }
        index++;
    }
    // shifting cards up accordingly
    for (int x = index; x < cardCount - 1; x++)
    {
        hand[x] = hand[x + 1];
    }
    cardCount --;
    return temp; // return 2 of clubs to be played first
}

int PlayerClass::GetScore() const
{
    // return player's score
    return score;
}

void PlayerClass::AddScore(int x)
{
    // add the sent in score (x) to player's current score
    score += x;
}

int PlayerClass::GetCount() const
{
    // return how many cards the player has in hand
    return cardCount;
}

void PlayerClass::Sort()
{
    if (cardCount >= 1)
    {
        int index;     // start point
        cardSuitType minSuitVal; // start min value string
        int maxCardVal; // value of card (2-14)

        // nested loop to sort a player's hand
        for (int i = 0; i < cardCount - 1; i++) 
        {
            index = i;           // set start value
            minSuitVal = hand[i].suits; // assign min value to first card's suit

            for (int j = i + 1; j < cardCount; j++) // start from next card in player's hand and compare
            {
                if (hand[j].suits < minSuitVal) // replace cards as needed
                {
                    minSuitVal = hand[j].suits;
                    index = j;
                }
            }
            swap(hand[index], hand[i]); // swap the two cards, putting the lowest found card
                                // at the top most position
        }
        // same loop as above, but to sort by card's value
        for (int i = 0; i < cardCount - 1; i++) 
        {
            index = i;
            maxCardVal = hand[i].value;
            minSuitVal = hand[i].suits;
            
            for (int j = i + 1; j < cardCount; j++)
            {
                // compare values of cards with same suits
                if (hand[j].suits == minSuitVal && hand[j].value > maxCardVal)
                {
                    maxCardVal = hand[j].value;
                    index = j;
                }
            }
            swap(hand[index], hand[i]);
        }
    }
}

CardType PlayerClass::PlaySelectedCard(int choice)
{
    // temp card to be returned
    choice --;
    CardType temp = hand[choice];

    // shift cards in hand accordingly
    for (int i = choice; i < cardCount - 1; i++)
    {
        hand[i] = hand[i + 1];
    }

    cardCount --; // decrement cards in hand by 1
    return temp; // return selected card
}

bool PlayerClass::IsValidChoice(cardSuitType suit, int choice) const
{
    choice --;
    // check if choice matches leading suit
    if (hand[choice].suits == suit)
    {
        return true;
    }

    bool noMatch = true; // no match for leading suit found
    for (int i = 0; i < cardCount; i++)
    {
        if (hand[i].suits == suit) // if leading suit found return false
        {
            noMatch = false;
            break;
        }
    }
    return noMatch; // return whether or not match is found
}