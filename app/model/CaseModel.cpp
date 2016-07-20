#include <iostream>
#include "CaseModel.h"
#include "../constraint/CasePieceConstraint.h"
#include "../../EternityII.h"

CaseModel::CaseModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    size = gameImportData.size;
    nbCases = gameImportData.depth;
    int depth = gameImportData.depth;

    // setting up max values

    piecesQte.resize(size,
        vector<int>(size, depth * 4));

    piecesQteHistory.resize(depth,
        vector<deque<CaseData>>(2));

    available.resize(size,
        vector<bool>(size, true));
    availableHistory.resize(depth,
        vector<deque<CaseData>>(2));

    // [x][y][n°piece][rotation]
    casePieces.resize(size,
        vector<vector<vector<bool>>>(size,
            vector<vector<bool>>(depth,
                vector<bool>(4, true))));
    casePiecesHistory.resize(depth,
        vector<deque<pair<CaseData, PieceData>>>(2));
}

void CaseModel::accept(
    const CaseData &caseData, const PieceData &pieceData, const int &depth
)
{
    // only update if it's not already done
    if (available[caseData.x][caseData.y]) {
        available[caseData.x][caseData.y] =
            false; // the case is not available anymore
        availableHistory[depth][ACCEPT].emplace_back(caseData);
        // the history has changed !!!

        addAcceptedEvent<CasePieceConstraint, CaseData>(
            static_cast<CasePieceConstraint &>(
                *observers[EternityII::CPCONSTRAINT]),
            caseData,
            depth
        );
    }
}

void CaseModel::accepted(const PieceData &pieceData, const int &depth)
{
    // it's a consequence of the update of pieceData, so we do it without checking anything
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            // if the case has the piece in it's domain and if it's available
            if (available[x][y]) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    if (casePieces[x][y][pieceData.id][rotation]) {
                        casePieces[x][y][pieceData.id][rotation] = false;
                        casePiecesHistory[depth][ACCEPT]
                            .emplace_back(make_pair(
                                CaseData(x, y),
                                PieceData(pieceData.id, rotation)
                            ));

                        --piecesQte[x][y];
                        piecesQteHistory[depth][ACCEPT].emplace_back(x, y);
                    }
                }
            }
        }
    }
}

void CaseModel::accepted(const CaseData &caseData, const int &depth)
{
    //TODO
}

void CaseModel::discard(
    const CaseData &caseData, const PieceData &pieceData, const int &depth)
{
    casePieces[caseData.x][caseData.y][pieceData.id][pieceData.rotation] =
        false;
    casePiecesHistory[depth][DISCARD].emplace_back(
        make_pair(caseData, pieceData)
    );

    --piecesQte[caseData.x][caseData.y];
    piecesQteHistory[depth][DISCARD].emplace_back(caseData);

    /* Does nothing for the moment
     * addDiscardedEvent<CasePieceConstraint, CaseData>(static_cast<CasePieceConstraint &>(*observers[0]),
        caseData,
        depth);*/
}

void CaseModel::discarded(const PieceData &pieceData, const int &depth)
{
// TODO DISCARD
}

void CaseModel::rollback(const int &depth, const bool &total /* = true */)
{
    int rollbackType;
    if (total) {
        rollbackType = DISCARD;
        rollback(depth, false);
    } else {
        rollbackType = ACCEPT;
    }

    deque<CaseData> &availQueue = availableHistory[depth][rollbackType];
    while (!availQueue.empty()) {
        available[availQueue.back().x][availQueue.back().y] = true;
        availQueue.pop_back();
    }

    deque<CaseData> &qteQueue = piecesQteHistory[depth][rollbackType];
    while (!qteQueue.empty()) {
        ++piecesQte[qteQueue.back().x][qteQueue.back().y];
        qteQueue.pop_back();
    }

    deque<pair<CaseData, PieceData>>
        &pcQueue = casePiecesHistory[depth][rollbackType];
    while (!pcQueue.empty()) {
        casePieces[pcQueue.back().first.x][pcQueue.back().first.y]
        [pcQueue.back().second.id][pcQueue.back().second.rotation] = true;
        pcQueue.pop_back();
    }
}

