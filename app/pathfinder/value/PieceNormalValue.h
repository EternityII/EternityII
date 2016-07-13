#ifndef ETERNITYII_PIECENORMALVALUE_H
#define ETERNITYII_PIECENORMALVALUE_H

#include "../../../core/pathfinder/value/ValueInterface.h"
#include "../../data/variable/CaseData.h"
#include "../../model/PieceModel.h"

class PieceNormalValue: public ValueInterface
{
private:
    PieceModel *_model;
    int pieceIterator = 0;
    int rotationIterator = 0;
    int actualDepth = 0;

public :
    PieceNormalValue(PieceModel &model)
    {
        this->_model = &model;
    }

    DataInterface *next(DataInterface &data) override
    {
        // TODO : Is the Model verifying itself, or is the solver/pathfinder verifying the Model
        return new PieceData(pieceIterator, rotationIterator);
    }

    /**
     * Checks if the variable can have a value
     *
     * @param data the variable
     * @param depth the current depth, for depth sensitive informations
     */
    const bool hasNext(DataInterface &data, const int &depth) override
    {
        int begin = 0;
        if (depth == actualDepth) {
            if (rotationIterator == 3) {
                ++begin;
                rotationIterator = 0;
            }
            begin += pieceIterator;
        }

        // static_cast is the best cast
        CaseData caseData = static_cast<CaseData &>(data);
        // for each piece if it's available
        for (int nPiece = begin; nPiece < _model->nbPieces; ++nPiece) {
            if (_model->available[nPiece]) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    // if the piece can be put on the case
                    if (_model->pieceCases[nPiece][rotation][caseData
                        .x][caseData.y]) {
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
