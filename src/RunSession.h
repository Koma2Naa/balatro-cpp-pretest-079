#ifndef RUNSESSION_H
#define RUNSESSION_H

#include <vector>
#include <string>
#include "ScoringSystem.h"
#include "modifiers/IModifier.h"
#include "Deck.h"

class RunSession {
private:
    int currentRound;
    int totalScore;
    int roundScore;   // Points earned in the current round only
    int targetScore;  // Points needed to clear the round
    int playsLeft;    // New: Limit for playing hands
    int discardsLeft; // Optional: Limit how many times you can discard
    bool isRunning;
    std::vector<IModifier*> inventory;
    
    // Pointer to the ScoringSystem to handle point math
    ScoringSystem* scoring;
    Deck* deck;

public:
    RunSession();
    ~RunSession();
    
    void startRun();
    void playHand();
    void visitShop();
    void endRun();
    
    bool isGameRunning() const { return isRunning; }
};

#endif