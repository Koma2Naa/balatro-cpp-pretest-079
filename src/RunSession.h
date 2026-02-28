#ifndef RUNSESSION_H
#define RUNSESSION_H

#include <vector>
#include <string>
#include "ScoringSystem.h" // Add this to recognize ScoringSystem and Card struct

class RunSession {
private:
    int currentRound;
    int totalScore;
    bool isRunning;
    
    // Pointer to the ScoringSystem to handle point math
    ScoringSystem* scoring;

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