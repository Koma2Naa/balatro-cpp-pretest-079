#include "RunSession.h"
#include "modifiers/ModifierFactory.h"
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
    for (auto item : inventory) {
        delete item;
    }
    delete scoring;
    delete deck;
}

void RunSession::startRun() {
    std::cout << "--- Starting New Run ---" << std::endl;
}

void RunSession::playHand() {
    deck->reset();
    deck->shuffle();

    roundScore = 0;   
    discardsLeft = 4; 
    
    // 1. Calculate the starting hand limit based on inventory
    int baseHands = 4;
    for (auto item : inventory) {
        baseHands = item->modifyHands(baseHands);
    }
    playsLeft = baseHands;

    // 2. Draw the initial hand
    std::vector<Card> currentHand = deck->drawHand(8);
    
    std::cout << "\n--- Round " << currentRound << " ---" << std::endl;
    std::cout << "TARGET SCORE: " << targetScore << std::endl;

    while (roundScore < targetScore && isRunning) {
        std::sort(currentHand.begin(), currentHand.end(), [](const Card& a, const Card& b) {
            return a.rank < b.rank;
        });

        std::cout << "\nPoints: " << roundScore << " / " << targetScore;
        std::cout << "\nPlays Left: " << playsLeft << " | Discards: " << discardsLeft << std::endl;

        // Check for Game Over
        if (playsLeft <= 0 && roundScore < targetScore) {
            std::cout << "\n!!! OUT OF HANDS - GAME OVER !!!" << std::endl;
            endRun(); 
            return; 
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
            std::vector<int> usedIndices;
            int idx;
            while (ss >> idx) {
                if (idx >= 1 && idx <= (int)currentHand.size()) {
                    selected.push_back(currentHand[idx - 1]);
                    usedIndices.push_back(idx - 1);
                }
            }

            // --- SCORING LOGIC START ---
            int baseValue = scoring->calculateBaseScore(selected);
            int multiplier = scoring->getHandMultiplier(selected);
            
            // Apply Item Bonuses from Inventory
            for (auto item : inventory) {
                multiplier = item->modifyMult(multiplier);
            }
            
            int finalHandScore = baseValue * multiplier;
            roundScore += finalHandScore;
            playsLeft--;
            
            std::cout << ">> Scored: " << baseValue << " x " << multiplier << " = " << finalHandScore << std::endl;
            // --- SCORING LOGIC END ---

            if (roundScore >= targetScore) {
                std::cout << "\n*** ROUND CLEARED! ***" << std::endl;
                targetScore *= 1.5; 
                currentRound++;
                return; // Round finished successfully
            }

            // Remove and replace cards
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
                if (idx >= 1 && idx <= (int)currentHand.size()) {
                    indicesToDiscard.push_back(idx - 1);
                }
            }

            if (indicesToDiscard.empty()) {
                std::cout << "No valid cards selected to discard." << std::endl;
                continue;
            }

            // Sort indices descending to avoid shifting issues during erase
            std::sort(indicesToDiscard.rbegin(), indicesToDiscard.rend());

            // Remove cards
            for (int i : indicesToDiscard) {
                currentHand.erase(currentHand.begin() + i);
            }

            // Draw replacements
            std::vector<Card> replacements = deck->drawHand(indicesToDiscard.size());
            for (const auto& nc : replacements) {
                currentHand.push_back(nc);
            }

            std::cout << "Discarded " << indicesToDiscard.size() << " cards and drew replacements!" << std::endl;
            discardsLeft--;
        }
        
    }
}

void RunSession::visitShop() {
    std::cout << "\n--- Welcome to the Shop ---" << std::endl;
    std::cout << "Available Items:" << std::endl;
    std::cout << "1. Energy Drink (+10 Mult, -2 Hands)" << std::endl;
    std::cout << "2. Tea (+3 Mult)" << std::endl;
    std::cout << "Enter choice (1-2) or [s] to skip: ";
    
    char choice;
    std::cin >> choice;
    
    IModifier* newItem = nullptr;
    if (choice == '1') {
        newItem = ModifierFactory::createModifier("energy");
    } else if (choice == '2') {
        newItem = ModifierFactory::createModifier("tea");
    }

    if (newItem) {
        inventory.push_back(newItem);
        std::cout << "Purchased: " << newItem->getName() << "!" << std::endl;
    }
}

void RunSession::endRun() {
    std::cout << "\n--- Run Ended ---" << std::endl;
    std::cout << "Final Score: " << totalScore << std::endl;
    isRunning = false;
}