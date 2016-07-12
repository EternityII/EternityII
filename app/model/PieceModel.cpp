#include "PieceModel.h"
#include "../constraint/CasePieceConstraint.h"

PieceModel::PieceModel(GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    nbPieces = gameImportData.depth;
    size = gameImportData.size;

    // Initializing tables
    casesQte.resize(nbPieces,
        vector<int>(4, nbPieces));
    casesQteHistory.resize(nbPieces,
        vector<vector<vector<int>>>(2,
            vector<vector<int>>(nbPieces,
                vector<int>(4, 0))));

    available.resize(nbPieces, true);
    availableHistory.resize(nbPieces,
        vector<vector<bool>>(2,
            vector<bool>(nbPieces, false)));

    // [n°piece][rotation][x][y]
    pieceCases.resize(nbPieces,
        vector<vector<vector<bool>>>(4,
            vector<vector<bool>>(size,
                vector<bool>(size, true))));

    pieceCasesHistory.resize(nbPieces,
        vector<vector<vector<vector<vector<bool>>>>>(2,
            vector<vector<vector<vector<bool>>>>(nbPieces,
                vector<vector<vector<bool >>>(4,
                    vector<vector<bool >>(size,
                        vector<bool>(size, false))))));

}

void PieceModel::accept(PieceData &pieceData, const int &depth)
{
    if (available[pieceData.id]) {
        available[pieceData.id] = false;
        availableHistory[depth][ACCEPT][pieceData.id] = true;

        addAcceptedEvent<CasePieceConstraint, PieceData>(
            static_cast<CasePieceConstraint &>(*observers[0]),
            pieceData,
            depth);
    }
}

void PieceModel::accepted(CaseData &caseData, const int &depth)
{
    // it's a consequence of the update of caseData, so we do it without checking anything
    for (int nPiece = 0; nPiece < nbPieces; ++nPiece) {
        if (available[nPiece]) { // if the piece is available
            for (int rotation = 0; rotation < 4; ++rotation) {
                // if the piece has the case in it's domain
                if (pieceCases[nPiece][rotation][caseData.x][caseData.y]) {
                    --casesQte[nPiece][rotation];
                    --casesQteHistory[depth][ACCEPT][nPiece][rotation];
                    //not anymore
                    pieceCases[nPiece][rotation][caseData.x][caseData.y] = false;
                    pieceCasesHistory[depth][ACCEPT][nPiece][rotation][caseData.x][caseData.y] = true;
                }
            }
        }
    }
}

void PieceModel::discard(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    pieceCases[pieceData.id][pieceData.rotation][caseData.x][caseData.y] = false;
    pieceCasesHistory[depth][DISCARD][pieceData.id][pieceData.rotation][caseData.x][caseData.y] = true;

    --casesQte[pieceData.id][pieceData.rotation];
    --casesQteHistory[depth][DISCARD][pieceData.id][pieceData.rotation];

    /* Not useful for the moment
     * addDiscardedEvent<CasePieceConstraint, PieceData>(static_cast<CasePieceConstraint &>(*observers[0]),
        pieceData,
        depth);*/
}

void PieceModel::discarded(CaseData &caseData, const int &depth)
{
    // TODO
}

void PieceModel::rollback(const int &depth)
{
    rollbackPartial(depth);
    for (int nPiece = 0; nPiece < nbPieces; ++nPiece) {
        for (int rotation = 0; rotation < 4; ++rotation) {
            if (casesQteHistory[depth][DISCARD][nPiece][rotation] != 0) {
                casesQte[nPiece][rotation] -= casesQteHistory[depth][DISCARD][nPiece][rotation];
                casesQteHistory[depth][DISCARD][nPiece][rotation] = 0;
            }


            for (int x = 0; x < size; ++x) {
                for (int y = 0; y < size; ++y) {
                    if (pieceCasesHistory[depth][DISCARD][nPiece][rotation][x][y]) {
                        pieceCases[nPiece][rotation][x][y] = true;
                        pieceCasesHistory[depth][DISCARD][nPiece][rotation][x][y] = false;
                    }
                }
            }
        }

        if (availableHistory[depth][DISCARD][nPiece]) {
            available[nPiece] = true;
            availableHistory[depth][DISCARD][nPiece] = false;
        }
    }
}

void PieceModel::rollbackPartial(const int &depth)
{
    for (int nPiece = 0; nPiece < nbPieces; ++nPiece) {
        for (int rotation = 0; rotation < 4; ++rotation) {
            if (casesQteHistory[depth][ACCEPT][nPiece][rotation] != 0) {
                casesQte[nPiece][rotation] -= casesQteHistory[depth][ACCEPT][nPiece][rotation];
                casesQteHistory[depth][ACCEPT][nPiece][rotation] = 0;
            }


            for (int x = 0; x < size; ++x) {
                for (int y = 0; y < size; ++y) {
                    if (pieceCasesHistory[depth][ACCEPT][nPiece][rotation][x][y]) {
                        pieceCases[nPiece][rotation][x][y] = true;
                        pieceCasesHistory[depth][ACCEPT][nPiece][rotation][x][y] = false;
                    }
                }
            }
        }

        if (availableHistory[depth][ACCEPT][nPiece]) {
            available[nPiece] = true;
            availableHistory[depth][ACCEPT][nPiece] = false;
        }
    }

}
