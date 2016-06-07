#ifndef ETERNITYII_VARIABLEINTERFACE_H
#define ETERNITYII_VARIABLEINTERFACE_H

#include "../structures/VariableData.h"
#include "../structures/GameData.h"

class VariableInterface
{
public:
    virtual void initialize(GameData &gameData) = 0;

    virtual VariableData next(int &depth) = 0;
};


#endif //ETERNITYII_VARIABLEINTERFACE_H
