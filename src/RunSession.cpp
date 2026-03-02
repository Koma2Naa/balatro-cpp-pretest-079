#include "RunSession.h"
#include <iostream>

RunSession::RunSession() : currentRound(1), totalScore(0), isRunning(true) {
    scoring = new ScoringSystem();
    deck = new Deck(); // Create the deck
    deck->shuffle();   // Shuffle at start of run
}

RunSession::~RunSession() {
    // Clean up pointers will happen here later
}

void RunSession::startRun() {
    std::cout << "--- Starting New Run ---" << std::endl;
}

void RunSession::playHand() {
    std::cout << "\n[Round " << currentRound << "] Playing hand..." << std::endl;
    
    std::vector<Card> hand = deck->drawHand(5);
    int base = scoring->calculateBaseScore(hand);
    int mult = scoring->getHandMultiplier(hand);
    
    int roundScore = base * mult;
    totalScore += roundScore;

    std::cout << "Hand: ";
    for(const auto& c : hand) std::cout << "[" << c.name << "] ";
    
    std::cout << "\nScore: " << base << " x " << mult << " = " << roundScore << std::endl;
    std::cout << "Total: " << totalScore << std::endl;
    
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