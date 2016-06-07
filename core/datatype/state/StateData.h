#ifndef ETERNITYII_STATEDATA_H
#define ETERNITYII_STATEDATA_H

#include "../../structures/GameData.h"

struct StateData
{
    virtual StateData(GameData &gameData) = 0;
};

#endif //ETERNITYII_STATEDATA_H
