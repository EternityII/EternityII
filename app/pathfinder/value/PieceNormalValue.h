#ifndef ETERNITYII_PIECENORMALVALUE_H
#define ETERNITYII_PIECENORMALVALUE_H

#include "../../../core/pathfinder/value/ValueInterface.h"
#include "../../data/variable/CaseData.h"
#include "../../data/value/PieceData.h"

class PieceNormalValue: public ValueInterface
{
    void initialize(GameImportData &gameData)
    {
        //TODO
    }

    DataInterface *next(DataInterface &dataInterface)
    {
        //TODO
        PieceData *pieceData = new PieceData(true);
        pieceData->id = 1;
        pieceData->rotation = 3;

        return pieceData;
    }

    const bool hasNext(DataInterface &dataInterface)
    {
        //TODO
        return true;
    }
};


#endif //ETERNITYII_PIECENORMALVALUE_H
