#include "CaseModel.h"
#include "../constraint/CasePieceConstraint.h"

void CaseModel::initialize(GameImportData &gameImportData)
{
    size = gameImportData.size;

    // setting up max values

    piecesQte.resize(size,
        vector<int>(size, gameImportData.depth));
    piecesQteHistory.resize(size,
        vector<vector<int>>(size,
            vector<int>(gameImportData.depth, 0)));

    isAvailable.resize(size, vector<bool>(size, true));
    isAvailableHistory.resize(size,
        vector<vector<bool>>(size,
            vector<bool>(gameImportData.depth, true)));

    // [x][y][n°piece][rotation]
    casePieces.resize(size,
        vector<vector<vector<bool>>>(size,
            vector<vector<bool>>(gameImportData.depth,
                vector<bool>(4, true))));
    casePiecesHistory.resize(size,
        vector<vector<vector<vector<bool>>>>(size,
            vector<vector<vector<bool>>>(gameImportData.depth,
                vector<vector<bool>>(4,
                    vector<bool>(gameImportData.depth, true)))));
}

void CaseModel::accept(CaseData &caseData, const int &depth)
{
    // only update if it's not already done
    if (isAvailable[caseData.x][caseData.y]) {
        isAvailable[caseData.x][caseData.y] = false; // the case is not available anymore
        isAvailableHistory[depth][caseData.x][caseData.y] = true;// the history has changed !!!

        dynamic_cast<CasePieceConstraint *>(observers[0])->accepted(caseData, depth);
    }
}

void CaseModel::accept(PieceData &pieceData, const int &depth)
{
    // it's a consequence of the update of pieceData, so we do it without checking anything
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            // if the case has the piece in it's domain
            if (casePieces[x][y][pieceData.id][pieceData.rotation]) {
                --piecesQte[x][y];
                --piecesQteHistory[x][y][depth];
                // not anymore
                casePieces[x][y][pieceData.id][pieceData.rotation] = false;
                casePiecesHistory[x][y][pieceData.id][pieceData.rotation][depth] = true;
            }
        }
    }
}

void CaseModel::discard(PieceData &pieceData, const int &depth)
{
    // TODO : don't know what todo yet
}

void CaseModel::discard(CaseData &caseData, const int &depth)
{
    // you can't discard a piece because it means that it [the puzzle] doesn't work
    // You do nothing John Sand
    // DO NOT TOUCH ... yet
}

void CaseModel::rollback(const int &from, const int &to)
{
    for (int depth = from; depth > to; --depth) {
        // they see me rolling ... back

        for (int x = 0; x < size; ++x) {
            for (int y = 0; y < size; ++y) {

                if (piecesQteHistory[x][y][depth] != 0) { // minimizing operations
                    piecesQte[x][y] -= piecesQteHistory[x][y][depth];
                    piecesQteHistory[x][y][depth] = 0;
                }
                if (isAvailableHistory[x][y][depth]) { // if the history has changed
                    isAvailable[x][y] = !isAvailable[x][y];
                    isAvailableHistory[x][y][depth] = false;
                }

                for (int nPieces = 0; nPieces < size * size; ++nPieces) {
                    for (int rotation = 0; rotation < 4; ++rotation) {
                        if (casePiecesHistory[x][y][nPieces][rotation][depth]) {
                            casePieces[x][y][nPieces][rotation] = !casePieces[x][y][nPieces][rotation];
                            casePiecesHistory[x][y][nPieces][rotation][depth] = false; // cleaning the depth
                        }
                    }
                }
            }
        }
    }
}
