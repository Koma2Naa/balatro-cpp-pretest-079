#include "RunSession.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

RunSession::RunSession() : currentRound(1), totalScore(0), isRunning(true) {
    scoring = new ScoringSystem();
    deck = new Deck(); // Create the deck
    deck->shuffle();   // Shuffle at start of run
    targetScore = 300; // Starting target
    playsLeft= 4;      // initial play limit
    discardsLeft = 4;  // Discard limit
}

RunSession::~RunSession() {
    // Clean up pointers will happen here later
}

void RunSession::startRun() {
    std::cout << "--- Starting New Run ---" << std::endl;
}

void RunSession::playHand() {
    roundScore = 0;   // Round Reset
    playsLeft = 4;    // Round Reset
    discardsLeft = 4; // Round Reset 
    std::vector<Card> currentHand = deck->drawHand(8);
    
    std::cout << "\n--- Round " << currentRound << " ---" << std::endl;
    std::cout << "TARGET SCORE: " << targetScore << std::endl;

    // Continue until the player meets the target
    while (roundScore < targetScore) {
        std::sort(currentHand.begin(), currentHand.end(), [](const Card& a, const Card& b) {
            return a.rank < b.rank;
        });

        std::cout << "\nPoints: " << roundScore << " / " << targetScore;
        std::cout << "\nPlays Left: " << playsLeft << " | Discards: " << discardsLeft << std::endl;

        if (playsLeft <= 0 && roundScore < targetScore) {
            std::cout << "\n!!! OUT OF HANDS - GAME OVER !!!" << std::endl;
            endRun(); 
            return; // Exit the function immediately
        }

        for (int i = 0; i < currentHand.size(); ++i) {
            std::cout << i + 1 << ": [" << currentHand[i].name << "]  ";
        }
        
        std::cout << "\nOptions: [p] Play Hand | [d] Discard" << std::endl;
        char choice;
        std::cin >> choice;

        if (choice == 'p') {
            std::cout << "Select cards (e.g., 1 2 5): ";
            std::string input;
            std::getline(std::cin >> std::ws, input);
            std::stringstream ss(input);
            
            std::vector<Card> selected;
            int idx;
            std::vector<int> usedIndices;
            while (ss >> idx) {
                if (idx >= 1 && idx <= currentHand.size()) {
                    selected.push_back(currentHand[idx - 1]);
                    usedIndices.push_back(idx - 1);
                }
            }

            int base = scoring->calculateBaseScore(selected);
            int mult = scoring->getHandMultiplier(selected);
            int score = base * mult;
            
            roundScore += score;
            playsLeft--;
            std::cout << ">> Scored: " << base << " x " << mult << " = " << score << std::endl;

            if (roundScore >= targetScore) {
                std::cout << "\n*** ROUND CLEARED! ***" << std::endl;
                targetScore *= 2; 
                currentRound++;
                break;
            }

            if (playsLeft <= 0 && roundScore < targetScore) {
                std::cout << "\n!!! OUT OF HANDS - GAME OVER !!!" << std::endl;
                this->endRun(); // This sets isRunning = false
                return; 
            }

            // Remove played cards and draw new ones
            std::sort(usedIndices.rbegin(), usedIndices.rend());
            for (int i : usedIndices) currentHand.erase(currentHand.begin() + i);
            
            std::vector<Card> replacements = deck->drawHand(usedIndices.size());
            for (const auto& c : replacements) currentHand.push_back(c);
        } 
        else if (choice == 'd') {
            if (discardsLeft <= 0) {
                std::cout << "!! No discards remaining !!" << std::endl;
                continue;
            }

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
            discardsLeft--;
        }
    }

    std::cout << "\n*** ROUND CLEARED! ***" << std::endl;
    totalScore += roundScore;
    targetScore *= 1.5;
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