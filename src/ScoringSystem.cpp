#include "ScoringSystem.h"

ScoringSystem::ScoringSystem() {}

int ScoringSystem::calculateBaseScore(const std::vector<Card>& hand) {
    int score = 0;
    for (const auto& card : hand) {
        score += card.rank; //sum the ranks of the cards
    }
    return score * 10;
}

int ScoringSystem::applyModifiers(int baseScore) {
    return baseScore;
}