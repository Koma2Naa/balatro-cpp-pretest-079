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
    
    //Test hand
    std::vector<Card> hand = {
        {5, "Hearts"},
        {7, "Spades"},
        {3, "Diamonds"}
    };
    
    int base = scoring->calculateBaseScore(hand);
    int finalScore = scoring->applyModifiers(base);
    
    totalScore += finalScore;
    std::cout << "Base Score (from cards): " << base << std::endl;
    std::cout << "Final Score (after modifiers): " << finalScore << std::endl;
    std::cout << "Total Run Score: " << totalScore << std::endl;
    
    currentRound++;
}

void RunSession::visitShop() {
    std::cout << "--- Entering Shop ---" << std::endl;
}

void RunSession::endRun() {
    std::cout << "\n--- Run Ended ---" << std::endl;
    std::cout << "Final Score: " << totalScore << std::endl;
    isRunning = false;
}