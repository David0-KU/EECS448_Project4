#include "Blackjack.h"
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
using namespace std;

Blackjack::Blackjack() {
    //initialize hand and handSize
}

int Blackjack::getHandSize() {
    return (handSize);
}

int Blackjack::getCard(int index) {
    if (index > handSize - 1 || index < 0) {
        return(-1);
    }
    else {
        return hand[index];
    }
}

int Blackjack::handValue() {//returns the optimal hand value for the player (counts aces as 1 if they would cause a bust, 11 otherwise)
    int val = 0;
    //determine value of hand not including aces:
    for (int i = 0; i < handSize; i++) {
        int cardVal = cardValue(hand[i]);
        int numAces = 0;
        
        if (cardVal != 11) {
            val += cardVal;
        }
        else {
            numAces++;
        }
    }
    
    //determine value of hand with aces:
    val += numAces - 1; //since you can't have 2 "11" aces without busting, consider all aces but one to be value of 1
    if (val + 11 <= 21) {//if counting the ace as 11 does not cause the hand to bust, do so
        val += 11;
    }
    else {//if an 11 would cause a bust, count it as a 1
        val += 1;
    }
    
    return(val);
    
}

bool Blackjack::isBust() {
    return(handValue() > 21);
}

void Blackjack::hit() {
    if (handSize < 22) {
    hand[handSize] = randomCard();
    handSize++;
    }
}

int Blackjack::randomCard() {
    srand((unsigned)time(NULL));
    return ((rand() % 52));
}

string Blackjack::parseCard(int card) {
    
    if (card == -1) {
        return("Empty");
    }
    
    int cardNum = card % 13;
    string cardName;
    
    switch(cardNum) {
        case 0: 
            cardName = "Ace";
            break;
        case 10:
            cardName = "Jack";
            break;
        case 11:
            cardName = "Queen";
            break;
        case 12:
            cardName = "King";
            break;
        default: 
            cardName = to_string(cardNum + 1);
    }
    
    if (card < 13) {
        return(cardName + " of Clubs");
    }
    else if (card < 26) {
        return(cardName + " of Diamonds");
    }
    else if (card < 39) {
        return(cardName + " of Hearts");
    }
    else {
        return(cardName + " of Spades");
    }
}

int Blackjack::cardValue(int card) {
    cardNum = card % 13;
    if (card < 0) {
        return(0);
    }
    else if (cardNum == 0) {
        return(11);
    }
    else if (cardNum > 8) {
        return(10);
    }
    else {
        return (cardNum + 1);
    }
}
