#include <iostream>
#include "CaseModel.h"
#include "../constraint/CasePieceConstraint.h"
#include "../../EternityII.h"

CaseModel::CaseModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    size = gameImportData.size;
    casesQte = gameImportData.depth;
    int depth = gameImportData.depth;

    // setting up max values

    pieceCount.resize(size,
        vector<int>(size, depth * 4));

    piecesCountHistory.resize(depth,
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

void CaseModel::allow(
    const CaseData &caseData, const PieceData &pieceData, const int &depth
)
{
    // only update if it's not already done
    if (available[caseData.x][caseData.y]) {
        // This case has only this piece in it's domain
        for (int pieceId = 0; pieceId < casesQte; ++pieceId) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                if (pieceData.id != pieceId && pieceData.rotation != pieceId) {
                    PieceData pieceDataPartialDeny(pieceId, rotation);

                    denyOne(caseData, pieceDataPartialDeny, depth, TRANSITORY);
                }
            }
        }

        // the case is not available anymore
        available[caseData.x][caseData.y] = false;
        availableHistory[depth][TRANSITORY].emplace_back(caseData);

        --pieceCount[caseData.x][caseData.y];
        piecesCountHistory[depth][TRANSITORY].emplace_back(caseData);

        // this case isn't available so deleting from all the domains
        // needed for var val choice
        addDenyEvent(static_cast<CasePieceConstraint &>
            (*observers[EternityII::CAPI_CONSTRAINT]),
            caseData,
            depth,
            TRANSITORY
        );
    }
}

void CaseModel::denyOne(
    const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    if (casePieces[caseData.x][caseData.y][pieceData.id][pieceData.rotation]) {
        casePieces[caseData.x][caseData.y][pieceData.id][pieceData.rotation]
            = false;
        casePiecesHistory[depth][persistent]
            .emplace_back(make_pair(caseData, pieceData));

        --pieceCount[caseData.x][caseData.y];
        piecesCountHistory[depth][persistent]
            .emplace_back(caseData);

        /* Does nothing, because of entrypoint
         * addDenyEvent(static_cast<CasePieceConstraint &>(*observers[EternityII::PCCONSTRAINT]),
            caseData,
            depth);*/
    }
}

void CaseModel::deny(const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            // if the case has the piece in it's domain and if it's available
            if (available[x][y]) {
                CaseData caseData(x, y);

                for (int rotation = 0; rotation < 4; ++rotation) {
                    PieceData pieceDataRotation(pieceData.id, rotation);

                    denyOne(caseData, pieceDataRotation, depth, persistent);
                }
            }
        }
    }
}

void CaseModel::deny(const CaseData &caseData,
    const int &depth,
    const int &persistent)
{
    if (available[caseData.x][caseData.y]) {
        for (int nPiece = 0; nPiece < casesQte; ++nPiece) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                PieceData pieceData(nPiece, rotation);

                denyOne(caseData, pieceData, depth, persistent);
            }
        }
    }
}

void CaseModel::rollback(const int &depth, const bool &total /* = true */)
{
    int type;
    if (total) {
        type = PERSISTENT;
        rollback(depth, false);
    } else {
        type = TRANSITORY;
    }

    auto &availQueue = availableHistory[depth][type];
    while (!availQueue.empty()) {
        available[availQueue.back().x][availQueue.back().y] = true;
        availQueue.pop_back();
    }

    auto &qteQueue = piecesCountHistory[depth][type];
    while (!qteQueue.empty()) {
        ++pieceCount[qteQueue.back().x][qteQueue.back().y];
        qteQueue.pop_back();
    }

    auto &pcQueue = casePiecesHistory[depth][type];
    while (!pcQueue.empty()) {
        casePieces[pcQueue.back().first.x][pcQueue.back().first.y]
        [pcQueue.back().second.id][pcQueue.back().second.rotation] = true;
        pcQueue.pop_back();
    }
}


