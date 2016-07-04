#include "PieceModel.h"
#include "../constraint/CasePieceConstraint.h"

void PieceModel::initialize(GameImportData &gameImportData)
{
    nbPieces = gameImportData.depth;
    size = gameImportData.size;

    casesQte.resize(nbPieces,
        vector<int>(4, nbPieces));
    casesQteHistory.resize(nbPieces,
        vector<vector<int>>(4,
            vector<int>(nbPieces, 0)));

    isAvailable.resize(nbPieces, vector<bool>(4, true));
    isAvailableHistory.resize(nbPieces,
        vector<vector<bool>>(4,
            vector<bool>(nbPieces, false)));

    // [n°piece][rotation][x][y]
    pieceCases.resize(nbPieces,
        vector<vector<vector<bool>>>(4,
            vector<vector<bool>>(size,
                vector<bool>(size, true))));

    pieceCasesHistory.resize(nbPieces,
        vector<vector<vector<vector<bool>>>>(4,
            vector<vector<vector<bool>>>(size,
                vector<vector<bool>>(size,
                    vector<bool>(nbPieces, true)))));

}

void PieceModel::accept(PieceData &pieceData, const int &depth)
{
    if (isAvailable[pieceData.id][pieceData.rotation]) {
        isAvailable[pieceData.id][pieceData.rotation] = false;
        isAvailableHistory[pieceData.id][pieceData.rotation][depth] = true;

        dynamic_cast<CasePieceConstraint *>(observers[0])->accepted(pieceData, depth);
    }
}

void PieceModel::accept(CaseData &caseData, const int &depth)
{
    // it's a consequence of the update of caseData, so we do it without checking anything
    for (int nPiece = 0; nPiece < nbPieces; ++nPiece) {
        for (int rotation = 0; rotation < 4; ++rotation) {
            // if the piece has the case in it's domain
            if (pieceCases[nPiece][rotation][caseData.x][caseData.y]) {
                --casesQte[nPiece][rotation];
                --casesQteHistory[nPiece][rotation][depth];
                //not anymore
                pieceCases[nPiece][rotation][caseData.x][caseData.y] = false;
                pieceCasesHistory[nPiece][rotation][caseData.x][caseData.y][depth] = true;
            }
        }
    }
}

void PieceModel::discard(PieceData &pieceData, const int &depth)
{
    // TODO
}

void PieceModel::discard(CaseData &caseData, const int &depth)
{
    // TODO
}

void PieceModel::rollback(const int &from, const int &to)
{
    for (int depth = from; depth > to; --depth) {
        // they see me rolling ... back
        for (int nPiece = 0; nPiece < nbPieces; ++nPiece) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                if (casesQteHistory[nPiece][rotation][depth] != 0) {
                    casesQte[nPiece][rotation] -= casesQteHistory[nPiece][rotation][depth];
                    casesQteHistory[nPiece][rotation][depth] = 0;
                }

                if (isAvailableHistory[nPiece][rotation][depth]) {
                    isAvailable[nPiece][rotation] = !isAvailable[nPiece][rotation];
                    isAvailableHistory[nPiece][rotation][depth] = false;
                }

                for (int x = 0; x < size; ++x) {
                    for (int y = 0; y < size; ++y) {
                        if (pieceCasesHistory[nPiece][rotation][x][y][depth]) {
                            pieceCases[nPiece][rotation][x][y] = !pieceCases[nPiece][rotation][x][y];
                            pieceCasesHistory[nPiece][rotation][x][y][depth] = false;
                        }
                    }
                }

            }
        }

    }
}
