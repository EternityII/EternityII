#include <iostream>
#include "PieceModel.h"
#include "../constraint/CasePieceConstraint.h"

PieceModel::PieceModel(GameImportData &gameImportData,
    EventManager &eventManager)
    : ModelInterface(eventManager)
{
    nbPieces = gameImportData.depth;
    size = gameImportData.size;

    // Initializing tables
    casesQte.resize(nbPieces,
        vector<int>(4, nbPieces));
    casesQteHistory.resize(nbPieces,
        vector<deque<PieceData>>(2));

    available.resize(nbPieces, true);
    availableHistory.resize(nbPieces,
        vector<deque<PieceData>>(2));

    // [n°piece][rotation][x][y]
    pieceCases.resize(nbPieces,
        vector<vector<vector<bool>>>(4,
            vector<vector<bool>>(size,
                vector<bool>(size, true))));

    pieceCasesHistory.resize(nbPieces,
        vector<deque<pair<PieceData, CaseData>>>(2));
}

void PieceModel::accept(PieceData &pieceData, const int &depth)
{
    if (available[pieceData.id]) {
        available[pieceData.id] = false;
        availableHistory[depth][ACCEPT].emplace_back(pieceData);

        addAcceptedEvent<CasePieceConstraint, PieceData>(
            static_cast<CasePieceConstraint &>(*observers[0]),
            pieceData,
            depth
        );
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
                    pieceCases[nPiece][rotation][caseData.x][caseData.y] =
                        false;
                    pieceCasesHistory[depth][ACCEPT]
                        .emplace_back(make_pair(PieceData(nPiece, rotation),
                            caseData));

                    --casesQte[nPiece][rotation];
                    casesQteHistory[depth][ACCEPT]
                        .emplace_back(nPiece, rotation);
                }
            }
        }
    }
}

void PieceModel::discard(CaseData &caseData,
    PieceData &pieceData,
    const int &depth)
{
    if (pieceCases[pieceData.id][pieceData.rotation][caseData.x][caseData.y]) {
        pieceCases[pieceData.id][pieceData.rotation][caseData.x][caseData.y] =
            false;
        pieceCasesHistory[depth][DISCARD]
            .emplace_back(make_pair(pieceData, caseData));

        --casesQte[pieceData.id][pieceData.rotation];
        casesQteHistory[depth][DISCARD]
            .emplace_back(pieceData);


        /* Not useful for the moment
         * addDiscardedEvent<CasePieceConstraint, PieceData>(static_cast<CasePieceConstraint &>(*observers[0]),
            pieceData,
            depth);*/
    }
}

void PieceModel::discarded(CaseData &caseData, const int &depth)
{
    // TODO
}

void PieceModel::rollback(const int &depth, const bool total /* = true */)
{
    int rollbackType;
    if (total) {
        rollbackType = DISCARD;
        rollback(depth, false);
    } else {
        rollbackType = ACCEPT;
    }

    deque<PieceData> &availQueue = availableHistory[depth][rollbackType];
    while (!availQueue.empty()) {
        available[availQueue.back().id] = true;
        availQueue.pop_back();
    }

    deque<PieceData> &qteQueue = casesQteHistory[depth][rollbackType];
    while (!qteQueue.empty()) {
        ++casesQte[qteQueue.back().id][qteQueue.back().rotation];
        qteQueue.pop_back();
    }

    deque<pair<PieceData, CaseData>> &pcQueue =
        pieceCasesHistory[depth][rollbackType];
    while (!pcQueue.empty()) {
        pieceCases[pcQueue.back().first.id][pcQueue.back().first.rotation]
        [pcQueue.back().second.x][pcQueue.back().second.y] = true;
        pcQueue.pop_back();
    }
}
