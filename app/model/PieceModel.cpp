#include "PieceModel.h"
#include "../constraint/CasePieceConstraint.h"
#include "../../EternityII.h"

PieceModel::PieceModel(const GameImportData &gameImportData,
    EventManager &eventManager)
    : ModelInterface(eventManager)
{
    nbPieces = gameImportData.depth;
    size = gameImportData.size;

    // Initializing tables
    casesQte.resize(nbPieces,
        vector<int>(4, nbPieces));
    casesQteHistory.resize(nbPieces,
        vector<deque<PieceData >>(2));

    available.resize(nbPieces, true);
    availableHistory.resize(nbPieces,
        vector<deque<PieceData >>(2));

    // [n°piece][rotation][x][y]
    pieceCases.resize(nbPieces,
        vector<vector<vector<bool >>>(4,
            vector<vector<bool >>(size,
                vector<bool>(size, true))));

    pieceCasesHistory.resize(nbPieces,
        vector<deque<pair<PieceData, CaseData >>>(2));
}

void PieceModel::allow(
    const CaseData &caseData, const PieceData &pieceData, const int &depth)
{
    if (available[pieceData.id]) {

        for (int xi = 0; xi < size; ++xi) {
            for (int yi = 0; yi < size; ++yi) {
                if (xi != caseData.x && yi != caseData.y) {
                    CaseData caseDataPartialDeny(xi, yi);

                    denyOne(caseDataPartialDeny, pieceData, depth, TRANSITORY);
                }
            }
        }

        available[pieceData.id] = false;
        availableHistory[depth][TRANSITORY].emplace_back(pieceData);

        // need to wait till the end
        addDenyEvent(static_cast<CasePieceConstraint &>
            (*observers[EternityII::CPCONSTRAINT]),
            pieceData,
            depth,
            TRANSITORY);
    }
}

void PieceModel::denyOne(
    const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    if (pieceCases[pieceData.id][pieceData.rotation][caseData.x][caseData.y]) {
        pieceCases[pieceData.id][pieceData.rotation][caseData.x][caseData.y] =
            false;
        pieceCasesHistory[depth][persistent]
            .emplace_back(make_pair(pieceData, caseData));

        --casesQte[pieceData.id][pieceData.rotation];
        casesQteHistory[depth][persistent]
            .emplace_back(pieceData);


        /* Not useful for the moment
         * addDenyEvent(static_cast<CasePieceConstraint &>(*observers[0]),
            pieceData,
            depth);*/
    }
}

void PieceModel::deny(const CaseData &caseData,
    const int &depth,
    const int &persistent)
{
    for (int nPiece = 0; nPiece < nbPieces; ++nPiece) {
        if (available[nPiece]) { // if the piece is available
            for (int rotation = 0; rotation < 4; ++rotation) {
                PieceData pieceData(nPiece, rotation);

                denyOne(caseData, pieceData, depth, persistent);
            }
        }
    }
}

void PieceModel::deny(const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    if (available[pieceData.id]) {

        for (int xi = 0; xi < size; ++xi) {
            for (int yi = 0; yi < size; ++yi) {
                CaseData caseData(xi, yi);

                for (int rotation = 0; rotation < 4; ++rotation) {
                    PieceData pieceDataPartialDeny(pieceData.id, rotation);

                    denyOne(caseData, pieceDataPartialDeny, depth, persistent);
                }
            }
        }
    }
}

void PieceModel::rollback(const int &depth, const bool &total /* = true*/)
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
        available[availQueue.back().id] = true;
        availQueue.pop_back();
    }

    auto &qteQueue = casesQteHistory[depth][type];
    while (!qteQueue.empty()) {
        ++casesQte[qteQueue.back().id][qteQueue.back().rotation];
        qteQueue.pop_back();
    }

    auto &pcQueue = pieceCasesHistory[depth][type];
    while (!pcQueue.empty()) {
        pieceCases[pcQueue.back().first.id][pcQueue.back().first.rotation]
        [pcQueue.back().second.x][pcQueue.back().second.y] = true;
        pcQueue.pop_back();
    }
}
