#include "RunSession.h"
#include <iostream>

int main() {
    RunSession game;
    
    game.startRun();
    
    // Loop for minimum 3 rounds as required by the assignment
    for(int i = 0; i < 3; ++i){
        game.playHand();
        game.visitShop();
    }
    
    game.endRun();
    
    return 0;
}