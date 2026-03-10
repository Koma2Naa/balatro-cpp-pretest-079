#include "IModifier.h"

class Tea : public IModifier {
public:
    std::string getName() const override { return "Tea (+3 Mult)"; }
    
    int modifyMult(int currentMulti) override { 
        return currentMulti + 3; 
    }
};