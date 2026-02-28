#ifndef RUNSESSION_H
#define RUNSESSION_H

#include <vector>
#include <string>
#include "ScoringSystem.h"
#include "Deck.h"

class RunSession {
private:
    int currentRound;
    int totalScore;
    bool isRunning;
    
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
    
    bool isActive() const { return isRunning; }
};

#endif