#ifndef MODIFIERFACTORY_H
#define MODIFIERFACTORY_H

#include "IModifier.h"
#include "EnergyDrink.h"
#include "Tea.h"
#include <string>

class ModifierFactory {
public:
    static IModifier* createModifier(const std::string& type) {
        if (type == "energy") return new EnergyDrink();
        if (type == "tea") return new Tea();
        return nullptr;
    }
};

#endif