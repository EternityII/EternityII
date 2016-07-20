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

void PieceModel::accept(
    const CaseData &caseData, const PieceData &pieceData, const int &depth)
{
    // avoiding unnecessary operations
    if (available[pieceData.id]) {
        available[pieceData.id] = false;
        availableHistory[depth][ACCEPT].emplace_back(pieceData);

        addAcceptedEvent<CasePieceConstraint, PieceData>(
            static_cast<CasePieceConstraint &>(*observers[EternityII::CPCONSTRAINT]),
            pieceData,
            depth
        );
    }
}

void PieceModel::accepted(const CaseData &caseData, const int &depth)
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

void PieceModel::accepted(const PieceData &pieceData, const int &depth)
{
    // TODO
}

void PieceModel::discard(
    const CaseData &caseData, const PieceData &pieceData, const int &depth)
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

void PieceModel::discarded(const CaseData &caseData, const int &depth)
{
    // TODO
}

void PieceModel::rollback(const int &depth, const bool &total /* = true*/)
{
    int type;
    if (total) {
        type = DISCARD;
        rollback(depth, false);
    } else {
        type = ACCEPT;
    }

    deque<PieceData> &availQueue = availableHistory[depth][type];
    while (!availQueue.empty()) {
        available[availQueue.back().id] = true;
        availQueue.pop_back();
    }

    deque<PieceData> &qteQueue = casesQteHistory[depth][type];
    while (!qteQueue.empty()) {
        ++casesQte[qteQueue.back().id][qteQueue.back().rotation];
        qteQueue.pop_back();
    }

    deque<pair<PieceData, CaseData>> &pcQueue =
        pieceCasesHistory[depth][type];
    while (!pcQueue.empty()) {
        pieceCases[pcQueue.back().first.id][pcQueue.back().first.rotation]
        [pcQueue.back().second.x][pcQueue.back().second.y] = true;
        pcQueue.pop_back();
    }
}
