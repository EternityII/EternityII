#ifndef ETERNITYII_DEFAULT_H
#define ETERNITYII_DEFAULT_H

#include "../../core/datatype/state/StateData.h"

struct Default: public StateData
{
    vector<int> qteCellsByPiece;

    vector<vector<int>> qtePiecesByCell;

    Default(GameData &gameData)
        : StateData(gameData)
    {

    };

};

#endif //ETERNITYII_DEFAULT_H
