#ifndef RUNSESSION_H
#define RUNSESSION_H

#include <vector>
#include <string>

// Forward declarations to keep it modular
class ScoringSystem;
class ShopSystem;

class RunSession {
private:
    int currentRound;
    int totalScore;
    bool isRunning;
    // Pointers to other systems for easy modification
    ScoringSystem* scoring;
    ShopSystem* shop;

public:
    RunSession();
    ~RunSession();
    
    void startRun();
    void playHand();
    void visitShop();
    void endRun();
    
    // Getter for the loop state
    bool isActive() const { return isRunning; }
};

#endif