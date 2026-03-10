#ifndef IMODIFIER_H
#define IMODIFIER_H

#include <string>

class IModifier {
public:
    virtual ~IModifier() {}
    virtual std::string getName() const = 0;
    
    // Logic for changing the multiplier
    virtual int modifyMult(int currentMulti) { return currentMulti; }
    
    // Logic for changing game stats like hand limits
    virtual int modifyHands(int currentHands) { return currentHands; }
};

#endif