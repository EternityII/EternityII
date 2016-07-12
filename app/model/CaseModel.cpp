#include <complex>
#include "CaseModel.h"
#include "../constraint/CasePieceConstraint.h"

CaseModel::CaseModel(GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    size = gameImportData.size;
    int depth = gameImportData.depth;

    // setting up max values

    piecesQte.resize(size,
        vector<int>(size, depth * 4));

    piecesQteHistory.resize(depth,
        vector<vector<vector<int>>>(2,
            vector<vector<int>>(size,
                vector<int>(size, 0))));

    available.resize(size,
        vector<bool>(size, true));
    availableHistory.resize(depth,
        vector<vector<vector<bool>>>(2,
            vector<vector<bool>>(size,
                vector<bool>(size, false))));

    // [x][y][n°piece][rotation]
    casePieces.resize(size,
        vector<vector<vector<bool>>>(size,
            vector<vector<bool>>(depth,
                vector<bool>(4, true))));
    casePiecesHistory.resize(depth,
        vector<vector<vector<vector<vector<bool>>>>>(2,
            vector<vector<vector<vector<bool>>>>(size,
                vector<vector<vector<bool>>>(size,
                    vector<vector<bool>>(depth,
                        vector<bool>(4, false))))));
}

void CaseModel::accept(CaseData &caseData, const int &depth)
{
    // only update if it's not already done
    if (available[caseData.x][caseData.y]) {
        available[caseData.x][caseData.y] = false; // the case is not available anymore
        availableHistory[depth][ACCEPT][caseData.x][caseData.y] = true;// the history has changed !!!


        addAcceptedEvent<CasePieceConstraint, CaseData>(
            static_cast<CasePieceConstraint &>(*observers[0]), caseData,
            depth);
    }
}

void CaseModel::accepted(PieceData &pieceData, const int &depth)
{
    // it's a consequence of the update of pieceData, so we do it without checking anything
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            // if the case has the piece in it's domain and if it's available
            if (available[x][y]) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    if (casePieces[x][y][pieceData.id][rotation]) {
                        --piecesQte[x][y];
                        --piecesQteHistory[depth][ACCEPT][x][y];
                        // not anymore
                        casePieces[x][y][pieceData.id][pieceData.rotation] = false;
                        casePiecesHistory[depth][ACCEPT][x][y][pieceData.id][pieceData.rotation] = true;
                    }
                }
            }
        }
    }
}

void CaseModel::discard(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    casePieces[caseData.x][caseData.y][pieceData.id][pieceData.rotation] = false;
    casePiecesHistory[depth][DISCARD][caseData.x][caseData.y][pieceData.id][pieceData.rotation] = true;

    --piecesQte[caseData.x][caseData.y];
    --piecesQteHistory[depth][DISCARD][caseData.x][caseData.y];

    /* Does nothing for the moment
     * addDiscardedEvent<CasePieceConstraint, CaseData>(static_cast<CasePieceConstraint &>(*observers[0]),
        caseData,
        depth);*/
}

void CaseModel::discarded(PieceData &pieceData, const int &depth)
{
// TODO
}

void CaseModel::rollback(const int &depth)
{
    rollbackPartial(depth);

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            if (piecesQteHistory[depth][DISCARD][x][y] != 0) { // minimizing operations
                piecesQte[x][y] -= piecesQteHistory[depth][1][x][y];
                piecesQteHistory[depth][DISCARD][x][y] = 0;
            }
            if (availableHistory[depth][DISCARD][x][y]) { // if the history has changed
                available[x][y] = true;
                availableHistory[depth][DISCARD][x][y] = false;
            }

            for (int nPieces = 0; nPieces < size * size; ++nPieces) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    if (casePiecesHistory[depth][DISCARD][x][y][nPieces][rotation]) {
                        casePieces[x][y][nPieces][rotation] = true;
                        casePiecesHistory[depth][DISCARD][x][y][nPieces][rotation] = false; // cleaning the depth
                    }
                }
            }
        }
    }
}

void CaseModel::rollbackPartial(const int &depth)
{
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {

            if (piecesQteHistory[depth][ACCEPT][x][y] != 0) { // minimizing operations
                piecesQte[x][y] -= piecesQteHistory[depth][1][x][y];
                piecesQteHistory[depth][ACCEPT][x][y] = 0;
            }
            if (availableHistory[depth][ACCEPT][x][y]) { // if the history has changed
                available[x][y] = true;
                availableHistory[depth][ACCEPT][x][y] = false;
            }

            for (int nPieces = 0; nPieces < size * size; ++nPieces) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    if (casePiecesHistory[depth][ACCEPT][x][y][nPieces][rotation]) {
                        casePieces[x][y][nPieces][rotation] = true;
                        casePiecesHistory[depth][ACCEPT][x][y][nPieces][rotation] = false; // cleaning the depth
                    }
                }
            }
        }
    }
}