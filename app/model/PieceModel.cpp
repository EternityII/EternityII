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
        vector<deque<PieceData *>>(2));

    available.resize(nbPieces, true);
    availableHistory.resize(nbPieces,
        vector<deque<PieceData *>>(2));

    // [n°piece][rotation][x][y]
    pieceCases.resize(nbPieces,
        vector<vector<vector<bool>>>(4,
            vector<vector<bool>>(size,
                vector<bool>(size, true))));

    pieceCasesHistory.resize(nbPieces,
        vector<deque<pair<PieceData *, CaseData *>>>(2));

    for (int variable = 1; variable < size - 1; ++variable) {
        CaseData caseXBeginEdge(0, variable);
        CaseData caseXEndEdge(size - 1, variable);
        CaseData caseYBeginEdge(variable, 0);
        CaseData caseYEndEdge(variable, size - 1);

        // interior piece cannot be put on a edge case
        for (int nInsidePiece = (size - 1) * 4;
             nInsidePiece > nbPieces;
             ++nInsidePiece) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                PieceData pieceData(nInsidePiece, rotation);

                discard(caseXBeginEdge, pieceData, 0);
                discard(caseXEndEdge, pieceData, 0);
                discard(caseYBeginEdge, pieceData, 0);
                discard(caseYEndEdge, pieceData, 0);
            }

        }

        // Edge pieces can be put only at a specific rotation on the edge
        for (int nBordPiece = 4; nBordPiece < (size - 1) * 4;
             ++nBordPiece) {
            PieceData pieceEdgeLeft(nBordPiece, 0);
            PieceData pieceEdgeTop(nBordPiece, 1);
            PieceData pieceEdgeRight(nBordPiece, 2);
            PieceData pieceEdgeBottom(nBordPiece, 3);

            discard(caseXBeginEdge, pieceEdgeTop, 0);
            discard(caseXBeginEdge, pieceEdgeRight, 0);
            discard(caseXBeginEdge, pieceEdgeBottom, 0);

            discard(caseYBeginEdge, pieceEdgeLeft, 0);
            discard(caseYBeginEdge, pieceEdgeRight, 0);
            discard(caseYBeginEdge, pieceEdgeBottom, 0);

            discard(caseXEndEdge, pieceEdgeLeft, 0);
            discard(caseXEndEdge, pieceEdgeTop, 0);
            discard(caseXEndEdge, pieceEdgeBottom, 0);

            discard(caseYEndEdge, pieceEdgeRight, 0);
            discard(caseYEndEdge, pieceEdgeTop, 0);
            discard(caseYEndEdge, pieceEdgeLeft, 0);
        }

        // corner piece cannot be put on edge
        for (int nCornerPiece = 0; nCornerPiece < 4; ++nCornerPiece) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                PieceData cornerPiece(nCornerPiece, rotation);

                discard(caseXBeginEdge, cornerPiece, 0);
                discard(caseXEndEdge, cornerPiece, 0);
                discard(caseYBeginEdge, cornerPiece, 0);
                discard(caseYEndEdge, cornerPiece, 0);
            }
        }
    }

    // Corner and Edge pieces cannot be put on an interior case
    for (int x = 1; x < size - 1; ++x) {
        for (int y = 1; y < size - 1; ++y) {
            CaseData caseInterieur(x, y);
            for (int nPiece = 0; nPiece < (size - 1) * 4; ++nPiece) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    PieceData pieceData(nPiece, rotation);
                    discard(caseInterieur, pieceData, 0);
                }
            }
        }
    }

    CaseData caseCornerLeftTop(0, 0);
    CaseData caseCornerTopRight(size - 1, 0);
    CaseData caseCornerRightBot(size - 1, size - 1);
    CaseData caseCornerBotLeft(0, size - 1);

    for (int nPiece = 4; nPiece < nbPieces; ++nPiece) {
        for (int rotation = 0; rotation < 4; ++rotation) {
            PieceData pieceData(nPiece, rotation);

            discard(caseCornerLeftTop, pieceData, 0);
            discard(caseCornerTopRight, pieceData, 0);
            discard(caseCornerRightBot, pieceData, 0);
            discard(caseCornerBotLeft, pieceData, 0);

        }
    }

    for (int nPieceCorner = 0; nPieceCorner < 4; ++nPieceCorner) {
        PieceData pieceCornerLeftTop(nPieceCorner, 0);
        discard(caseCornerTopRight, pieceCornerLeftTop, 0);
        discard(caseCornerRightBot, pieceCornerLeftTop, 0);
        discard(caseCornerBotLeft, pieceCornerLeftTop, 0);

        PieceData pieceCornerTopRight(nPieceCorner, 1);
        discard(caseCornerLeftTop, pieceCornerTopRight, 0);
        discard(caseCornerRightBot, pieceCornerTopRight, 0);
        discard(caseCornerBotLeft, pieceCornerTopRight, 0);

        PieceData pieceCornerRightBot(nPieceCorner, 2);
        discard(caseCornerLeftTop, pieceCornerRightBot, 0);
        discard(caseCornerTopRight, pieceCornerRightBot, 0);
        discard(caseCornerBotLeft, pieceCornerRightBot, 0);

        PieceData pieceCornerBotLeft(nPieceCorner, 3);
        discard(caseCornerLeftTop, pieceCornerBotLeft, 0);
        discard(caseCornerTopRight, pieceCornerBotLeft, 0);
        discard(caseCornerRightBot, pieceCornerBotLeft, 0);
    }

}

void PieceModel::accept(PieceData &pieceData, const int &depth)
{
    if (available[pieceData.id]) {
        available[pieceData.id] = false;
        availableHistory[depth][ACCEPT].emplace_back(
            new PieceData(pieceData)
        );

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
                    casesQteHistory[depth][ACCEPT]
                        .emplace_back(new PieceData(nPiece, rotation));

                    pieceCases[nPiece][rotation][caseData.x][caseData.y] =
                        false;
                    pieceCasesHistory[depth][ACCEPT]
                        .emplace_back(
                            make_pair(new PieceData(nPiece, rotation),
                                new CaseData(caseData)));
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
            .emplace_back(
                make_pair(new PieceData(pieceData),
                    new CaseData(caseData)));

        --casesQte[pieceData.id][pieceData.rotation];
        casesQteHistory[depth][DISCARD]
            .emplace_back(new PieceData(pieceData));


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
    }
    else {
        rollbackType = ACCEPT;
    }

    deque<PieceData *> &availQueue = availableHistory[depth][rollbackType];
    while (!availQueue.empty()) {
        available[availQueue.back()->id] = true;
        delete availQueue.back();
        availQueue.pop_back();
    }

    deque<PieceData *> &qteQueue = casesQteHistory[depth][rollbackType];
    while (!qteQueue.empty()) {
        ++casesQte[qteQueue.back()->id][qteQueue.back()->rotation];
        delete qteQueue.back();
        qteQueue.pop_back();
    }

    deque<pair<PieceData *, CaseData *>> &pcQueue =
        pieceCasesHistory[depth][rollbackType];
    while (!pcQueue.empty()) {
        pieceCases[pcQueue.back().first->id][pcQueue.back().first->rotation]
        [pcQueue.back().second->x][pcQueue.back().second->y] = true;
        delete pcQueue.back().first;
        delete pcQueue.back().second;
        pcQueue.pop_back();
    }
}
