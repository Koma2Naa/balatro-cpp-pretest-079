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
    std::cout << "\n[Round " << currentRound << "] Drawing and playing hand..." << std::endl;
    
    // Draw 5 cards from the deck
    std::vector<Card> hand = deck->drawHand(5);
    
    int base = scoring->calculateBaseScore(hand);
    int finalScore = scoring->applyModifiers(base);
    
    totalScore += finalScore;
    
    // Show what was drawn
    std::cout << "Hand played: ";
    for(const auto& c : hand) std::cout << "[" << c.name << "] ";
    
    std::cout << "\nBase Score: " << base << " | Final Score: " << finalScore << std::endl;
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