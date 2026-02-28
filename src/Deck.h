#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "ScoringSystem.h"

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck();
    void shuffle();
    std::vector<Card> drawHand(int handSize);
    void reset();
};

#endif