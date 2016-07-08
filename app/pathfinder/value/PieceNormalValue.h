#ifndef ETERNITYII_PIECENORMALVALUE_H
#define ETERNITYII_PIECENORMALVALUE_H

#include "../../../core/pathfinder/value/ValueInterface.h"
#include "../../data/variable/CaseData.h"
#include "../../data/value/PieceData.h"

class PieceNormalValue: public ValueInterface
{
    PieceModel *_modelInterface;
    int pieceIterator = 0;
    int rotationIterator = 0;
public :
    void initialize(ModelInterface &modelInterface) override
    {
        this->_modelInterface = static_cast<PieceModel *>(&modelInterface);
    }

    DataInterface *next(DataInterface &dataInterface) override
    {
        // TODO : Is the Model verifying itself, or is the solver/pathfinder verifying the Model
        PieceData *pieceData = new PieceData(pieceIterator, rotationIterator);
        return pieceData;
    }

    const bool hasNext(DataInterface &dataInterface, const int &depth) override
    {
        CaseData caseData = static_cast<CaseData &>(dataInterface);
        for (int nPiece = 0; nPiece < _modelInterface->nbPieces; ++nPiece) {
            if (_modelInterface->available[nPiece]) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    if (_modelInterface->pieceCases[nPiece][rotation][caseData.x][caseData.y]) {
                        pieceIterator = nPiece;
                        rotationIterator = rotation;
                        return true;
                    }
                }
            }
        }
        return false;
    }
};


#endif //ETERNITYII_PIECENORMALVALUE_H
