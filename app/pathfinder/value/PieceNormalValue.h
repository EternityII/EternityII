#ifndef ETERNITYII_PIECENORMALVALUE_H
#define ETERNITYII_PIECENORMALVALUE_H

#include "../../../core/pathfinder/value/ValueInterface.h"

class PieceNormalValue: public ValueInterface
{
    void initialize(GameImportData &gameData)
    {
        //TODO
    }

    unique_ptr<DataInterface> next(DataInterface &dataInterface)
    {
        //TODO
        unique_ptr<PieceData> pieceData = make_unique<PieceData>(true);
        pieceData->id = 1;
        pieceData->rotation = 5;

        return move(pieceData);

    }
};


#endif //ETERNITYII_PIECENORMALVALUE_H
