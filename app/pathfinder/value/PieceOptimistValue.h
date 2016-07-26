#ifndef ETERNITYII_PIECEOPTIMISTVALUE_H
#define ETERNITYII_PIECEOPTIMISTVALUE_H

#include "../../../core/pathfinder/value/ValueInterface.h"
#include "../../data/variable/CaseData.h"
#include "../../model/PieceModel.h"

class PieceOptimistValue: public ValueInterface
{
private:
    PieceModel &_model;
    int pieceIterator = 0;
    int rotationIterator = 0;

public :
    PieceOptimistValue(PieceModel &model)
        : _model(model)
    { }

    DataInterface *next(DataInterface &data) override
    {
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
        int max = 0;

        // static_cast is the best cast
        CaseData caseData = static_cast<CaseData &>(data);
        // for each piece if it's available
        for (int nPiece = 0; nPiece < _model.piecesQte; ++nPiece) {
            if (_model.available[nPiece]) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    // if the piece can be put on the case
                    if (_model.pieceCases[nPiece][rotation]
                    [caseData.x][caseData.y]) {
                        if (_model.casesCount[nPiece][rotation] == 0) {
                            return false;
                        }
                        if (_model.casesCount[nPiece][rotation] > max) {
                            max = _model.casesCount[nPiece][rotation];
                            pieceIterator = nPiece;
                            rotationIterator = rotation;
                        }
                    }
                }
            }
        }

        return max != 0;
    }
};


#endif //ETERNITYII_PIECEOPTIMISTVALUE_H
