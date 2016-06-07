#ifndef ETERNITYII_VALUEINTERFACE_H
#define ETERNITYII_VALUEINTERFACE_H

#include "../structures/ValueData.h"

class ValueInterface
{
public:
    virtual void initialize(GameData &gameData) = 0;

    virtual ValueData next(VariableData &variableData) = 0;
};

#endif //ETERNITYII_VALUEINTERFACE_H
