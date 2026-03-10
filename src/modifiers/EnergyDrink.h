#include "IModifier.h"

class EnergyDrink : public IModifier {
public:
    std::string getName() const override { return "Energy Drink (+10 Mult, -2 Hands)"; }
    
    int modifyMult(int currentMulti) override { 
        return currentMulti + 10; 
    }
    
    int modifyHands(int currentHands) override { 
        return currentHands - 2; 
    }
};