#ifndef ETERNITYII_PIECENORMALVALUE_H
#define ETERNITYII_PIECENORMALVALUE_H

#include "../../../core/pathfinder/value/ValueInterface.h"

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
        pieceData->rotation = 5;

        return pieceData;
    }

    const bool hasNext(DataInterface &dataInterface)
    {
        //TODO
        return false;
    }
};


#endif //ETERNITYII_PIECENORMALVALUE_H
