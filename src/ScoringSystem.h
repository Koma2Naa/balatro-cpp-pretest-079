#ifndef SCORINGSYSTEM_H
#define SCORINGSYSTEM_H

#include <vector>
#include <string>
#include <map>

struct Card {
    int rank;
    std::string name;
};

class ScoringSystem {
public:
    ScoringSystem();
    int calculateBaseScore(const std::vector<Card>& hand);
    int getHandMultiplier(const std::vector<Card>& hand);
    int applyModifiers(int baseScore);

private:
    bool isFlush(const std::vector<Card>& hand);
    bool isStraight(std::vector<int> ranks);
};

#endif