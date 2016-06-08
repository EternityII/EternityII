#ifndef ETERNITYII_STATEDATA_H
#define ETERNITYII_STATEDATA_H

#include "../../structures/GameData.h"

struct StateData
{
    StateData()
    { }

    StateData(StateData &stateData)
    { }

    virtual void initialize(const GameData &gameData) = 0;
};

#endif //ETERNITYII_STATEDATA_H
