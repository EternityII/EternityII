#ifndef ETERNITYII_PIECEPESSIMISTVALUE_H
#define ETERNITYII_PIECEPESSIMISTVALUE_H


#include "../../../core/pathfinder/value/ValueInterface.h"
#include "../../model/PieceModel.h"

class PiecePessimistValue: public ValueInterface
{
private:
    PieceModel &_model;
    int pieceIterator = 0;
    int rotationIterator = 0;

public :
    PiecePessimistValue(PieceModel &model)
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
        int min = _model.piecesQte + 1;

        // static_cast is the best cast
        CaseData caseData = static_cast<CaseData &>(data);
        // for each piece if it's available
        for (int nPiece = 0; nPiece < _model.piecesQte; ++nPiece) {
            if (_model.available[nPiece]) {
                bool hasHope = false;
                for (int rotation = 0; rotation < 4; ++rotation) {
                    if (_model.casesCount[nPiece][rotation] != 0) {
                        hasHope = true;
                    }

                    if (_model.pieceCases[nPiece][rotation]
                    [caseData.x][caseData.y]) {
                        // if the piece can be put on the case
                        if (_model.casesCount[nPiece][rotation] == 1) {
                            pieceIterator = nPiece;
                            rotationIterator = rotation;
                            return true;
                        } else if (_model.casesCount[nPiece][rotation] < min) {
                            min = _model.casesCount[nPiece][rotation];
                            pieceIterator = nPiece;
                            rotationIterator = rotation;
                        }
                    }
                }
                if (!hasHope) {
                    return false;
                }
            }
        }

        return min != _model.piecesQte + 1;
    }
};


#endif //ETERNITYII_PIECEPESSIMISTVALUE_H
