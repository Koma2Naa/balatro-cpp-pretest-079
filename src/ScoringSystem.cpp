#include "ScoringSystem.h"

ScoringSystem::ScoringSystem() {}

int ScoringSystem::calculateBaseScore(const std::vector<Card>& hand) {
    int score = 0;
    for (const auto& card : hand) {
        score += card.rank; //sum of the cards
    }
    return score;
}

int ScoringSystem::applyModifiers(int baseScore) {
    return baseScore;
}