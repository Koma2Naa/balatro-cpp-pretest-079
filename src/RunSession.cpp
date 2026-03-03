#include "RunSession.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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
    std::cout << "\n--- Round " << currentRound << " ---" << std::endl;
    
    //Draw 8 cards to the player's hand
    std::vector<Card> currentHand = deck->drawHand(8);
    bool handPlayed = false;

    while (!handPlayed) {
        // SORTING HAPPENS HERE
        std::sort(currentHand.begin(), currentHand.end(), [](const Card& a, const Card& b) {
            return a.rank < b.rank;
        });

        std::cout << "\nYour Hand:" << std::endl;
        for (int i = 0; i < currentHand.size(); ++i) {
            std::cout << i + 1 << ": [" << currentHand[i].name << "]  ";
        }
        
        std::cout << "\n\nOptions: [p] Play Hand | [d] Discard" << std::endl;
        char choice;
        std::cin >> choice;

        if (choice == 'p') {
            std::cout << "Enter card numbers to play (e.g., 1 2 5): ";
            std::string input;
            std::getline(std::cin >> std::ws, input);
            std::stringstream ss(input);
            
            std::vector<Card> selectedCards;
            int index;
            while (ss >> index) {
                if (index >= 1 && index <= currentHand.size()) {
                    selectedCards.push_back(currentHand[index - 1]);
                }
            }

            // Calculate Score
            int base = scoring->calculateBaseScore(selectedCards);
            int mult = scoring->getHandMultiplier(selectedCards);
            int score = base * mult;
            
            totalScore += score;
            std::cout << "YOU PLAYED: " << selectedCards.size() << " cards." << std::endl;
            std::cout << "SCORE: " << base << " x " << mult << " = " << score << std::endl;
            
            handPlayed = true;
        } 
        else if (choice == 'd') {
            std::cout << "Enter card numbers to discard (e.g., 1 3 4): ";
            std::string discardInput;
            std::getline(std::cin >> std::ws, discardInput);
            std::stringstream ssD(discardInput);
            
            std::vector<int> indicesToDiscard;
            int idx;
            while (ssD >> idx) {
                if (idx >= 1 && idx <= currentHand.size()) {
                    // Store 0-based index
                    indicesToDiscard.push_back(idx - 1);
                }
            }

            // Sort indices in descending order to avoid shifting issues when erasing
            std::sort(indicesToDiscard.rbegin(), indicesToDiscard.rend());

            // Remove selected cards from currentHand
            for (int i : indicesToDiscard) {
                currentHand.erase(currentHand.begin() + i);
            }

            // Draw new cards to replace them (back up to 8 cards)
            int cardsNeeded = 8 - currentHand.size();
            std::vector<Card> newCards = deck->drawHand(cardsNeeded);
            
            for (const auto& nc : newCards) {
                currentHand.push_back(nc);
            }

            std::cout << "Discarded " << indicesToDiscard.size() << " cards and drew replacements!" << std::endl;
        }
    }
    
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