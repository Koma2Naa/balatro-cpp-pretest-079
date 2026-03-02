#include "Deck.h"

Deck::Deck() {
    reset();
}

void Deck::reset() {
    cards.clear();
    std::string suits[] = {"Hearts", "Spades", "Diamonds", "Clubs"};
    for (const std::string& s : suits) {
        // Ace
        cards.push_back({14, "Ace of " + s});
        
        // 2 through 10
        for (int r = 2; r <= 10; ++r) {
            cards.push_back({r, std::to_string(r) + " of " + s});
        }
        
        // Face Cards
        cards.push_back({11, "Jack of " + s});
        cards.push_back({12, "Queen of " + s});
        cards.push_back({13, "King of " + s});
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