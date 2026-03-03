#include "Deck.h"

Deck::Deck() {
    reset();
}

void Deck::reset() {
    cards.clear();
    // Using Unicode symbols for suits
    struct Suit { std::string name; std::string symbol; };
    Suit suits[] = { {"Hearts", "♥"}, {"Spades", "♠"}, {"Diamonds", "♦"}, {"Clubs", "♣"} };
    
    for (const auto& s : suits) {
        // Ace (Rank 14)
        cards.push_back({14, "A" + s.symbol});
        
        // 2 - 10
        for (int r = 2; r <= 10; ++r) {
            cards.push_back({r, std::to_string(r) + s.symbol});
        }
        
        // Face Cards (Ranks 11-13)
        cards.push_back({11, "J" + s.symbol});
        cards.push_back({12, "Q" + s.symbol});
        cards.push_back({13, "K" + s.symbol});
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::vector<Card> Deck::drawHand(int handSize) {
    std::vector<Card> hand;
    for (int i = 0; i < handSize && !cards.empty(); ++i) {
        hand.push_back(cards.back());
        cards.pop_back();
    }
    return hand;
}