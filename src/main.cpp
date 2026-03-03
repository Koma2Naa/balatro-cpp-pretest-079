#include "RunSession.h"
#include <iostream>

int main() {
    RunSession game;
    game.startRun();

    // Only continue if the game hasn't hit a Game Over state
    while (game.isGameRunning()) { 
        game.playHand();
        
        if (game.isGameRunning()) {
            game.visitShop();
        }
    }

    std::cout << "Thanks for playing!\n" << std::endl;
    return 0;
}