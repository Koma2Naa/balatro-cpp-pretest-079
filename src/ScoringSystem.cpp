#include "ScoringSystem.h"
#include <algorithm>

ScoringSystem::ScoringSystem() {}

int ScoringSystem::calculateBaseScore(const std::vector<Card>& hand) {
    int score = 0;
    for (const auto& card : hand) {
        if (card.rank == 14) { 
            score += 11; // Ace is worth 11 points
        } else if (card.rank >= 11) { 
            score += 10; // J, Q, K are all worth 10 points
        } else {
            score += card.rank; // 2-10 are face value
        }
    }
    return score; // Your Balatro-style multiplier
}

int ScoringSystem::getHandMultiplier(const std::vector<Card>& hand) {
    if (hand.empty()) return 1;

    std::map<int, int> counts;
    std::vector<int> ranks;
    for (const auto& c : hand) {
        counts[c.rank]++;
        ranks.push_back(c.rank);
    }
    std::sort(ranks.begin(), ranks.end());

    bool flush = isFlush(hand);
    bool straight = isStraight(ranks);

    // Poker Hand Multipliers (Strategy Pattern)
    if (straight && flush) return 8; 
    for (auto const& [rank, count] : counts) if (count == 4) return 7;

    bool hasThree = false;
    int pairCount = 0;
    for (auto const& [rank, count] : counts) {
        if (count == 3) hasThree = true;
        if (count == 2) pairCount++;
    }
    
    if (hasThree && pairCount >= 1) return 6; // Full House
    if (flush) return 5;
    if (straight) return 4;
    if (hasThree) return 3;
    if (pairCount >= 2) return 2; // Two Pair
    if (pairCount == 1) return 2; // One Pair

    return 1; // High Card
}

bool ScoringSystem::isFlush(const std::vector<Card>& hand) {
    if (hand.size() < 5) return false; // In Balatro, a flush needs 5 cards

    size_t pos = hand[0].name.find(" of ");
    if (pos == std::string::npos) return false; // Safety check
    
    std::string firstSuit = hand[0].name.substr(pos + 4);
    
    for (const auto& c : hand) {
        if (c.name.find(firstSuit) == std::string::npos) return false;
    }
    return true;
}

bool ScoringSystem::isStraight(std::vector<int> ranks) {
    // 1. Sort is required before unique
    std::sort(ranks.begin(), ranks.end());
    
    // 2. Actually remove the duplicates from the vector
    ranks.erase(std::unique(ranks.begin(), ranks.end()), ranks.end());
    
    // 3. Must be exactly 5 unique cards for a straight
    if (ranks.size() < 5) return false;
    
    // 4. Check if the gap between max and min is 4 (e.g., 2,3,4,5,6 -> 6-2 = 4)
    return (ranks.back() - ranks.front() == 4);
}

int ScoringSystem::applyModifiers(int baseScore) {
    return baseScore; // Placeholder
    }