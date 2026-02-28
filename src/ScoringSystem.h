#ifndef SCORINGSYSTEM_H
#define SCORINGSYSTEM_H

#include <vector>
#include <string>

// A simple struct to represent a card
struct Card {
    int rank;
    std::string name;
};

class ScoringSystem {
public:
    ScoringSystem();
    
    // Logic for calculating the raw score from a hand of cards
    int calculateBaseScore(const std::vector<Card>& hand);
    
    // Logic for applying modifiers (like Double or Flat bonuses)
    int applyModifiers(int baseScore);
};

#endif