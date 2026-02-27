#include "RunSession.h"
#include <iostream>

RunSession::RunSession() : currentRound(1), totalScore(0), isRunning(true) {
    // These will be implemented in future commits
    // scoring = new ScoringSystem();
    // shop = new ShopSystem();
}

RunSession::~RunSession() {
    // Clean up pointers will happen here later
}

void RunSession::startRun() {
    std::cout << "--- Starting New Run ---" << std::endl;
}

void RunSession::playHand() {
    std::cout << "\n[Round " << currentRound << "] Playing hand..." << std::endl;
    int roundScore = 100; // Placeholder base score
    totalScore += roundScore;
    std::cout << "Round Score: " << roundScore << " | Total Score: " << totalScore << std::endl;
}

void RunSession::visitShop() {
    std::cout << "--- Entering Shop ---" << std::endl;
}

void RunSession::endRun() {
    std::cout << "\n--- Run Ended ---" << std::endl;
    std::cout << "Final Score: " << totalScore << std::endl;
    isRunning = false;
}