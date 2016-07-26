#include "CasePieceConstraint.h"

CasePieceConstraint::CasePieceConstraint(CaseModel &caseModel,
    PieceModel &pieceModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(caseModel), _second(pieceModel)
{
    _first.add(*this);
    _second.add(*this);

    // because entry point u know
    for (int variable = 1; variable < caseModel.size - 1; ++variable) {
        CaseData caseXBeginEdge(0, variable);
        CaseData caseXEndEdge(caseModel.size - 1, variable);
        CaseData caseYBeginEdge(variable, 0);
        CaseData caseYEndEdge(variable, caseModel.size - 1);

        // interior piece cannot be put on a edge case
        for (int nInsidePiece = (caseModel.size - 1) * 4;
             nInsidePiece < pieceModel.piecesQte;
             ++nInsidePiece) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                PieceData pieceData(nInsidePiece, rotation);

                denyOne(caseXBeginEdge, pieceData, 0, 0);
                denyOne(caseXEndEdge, pieceData, 0, 0);
                denyOne(caseYBeginEdge, pieceData, 0, 0);
                denyOne(caseYEndEdge, pieceData, 0, 0);
            }

        }

        // Edge pieces can be put only at a specific rotation on the edge
        for (int nBordPiece = 4; nBordPiece < (caseModel.size - 1) * 4;
             ++nBordPiece) {
            PieceData pieceEdgeLeft(nBordPiece, 0);
            PieceData pieceEdgeTop(nBordPiece, 1);
            PieceData pieceEdgeRight(nBordPiece, 2);
            PieceData pieceEdgeBottom(nBordPiece, 3);

            denyOne(caseXBeginEdge, pieceEdgeTop, 0, 0);
            denyOne(caseXBeginEdge, pieceEdgeRight, 0, 0);
            denyOne(caseXBeginEdge, pieceEdgeBottom, 0, 0);

            denyOne(caseYBeginEdge, pieceEdgeLeft, 0, 0);
            denyOne(caseYBeginEdge, pieceEdgeRight, 0, 0);
            denyOne(caseYBeginEdge, pieceEdgeBottom, 0, 0);

            denyOne(caseXEndEdge, pieceEdgeLeft, 0, 0);
            denyOne(caseXEndEdge, pieceEdgeTop, 0, 0);
            denyOne(caseXEndEdge, pieceEdgeBottom, 0, 0);

            denyOne(caseYEndEdge, pieceEdgeRight, 0, 0);
            denyOne(caseYEndEdge, pieceEdgeTop, 0, 0);
            denyOne(caseYEndEdge, pieceEdgeLeft, 0, 0);
        }

        // corner piece cannot be put on edge
        for (int nCornerPiece = 0; nCornerPiece < 4; ++nCornerPiece) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                PieceData cornerPiece(nCornerPiece, rotation);

                denyOne(caseXBeginEdge, cornerPiece, 0, 0);
                denyOne(caseXEndEdge, cornerPiece, 0, 0);
                denyOne(caseYBeginEdge, cornerPiece, 0, 0);
                denyOne(caseYEndEdge, cornerPiece, 0, 0);
            }
        }
    }

    // Corner and Edge pieces cannot be put on an interior case
    for (int x = 1; x < caseModel.size - 1; ++x) {
        for (int y = 1; y < caseModel.size - 1; ++y) {
            CaseData caseInterieur(x, y);
            for (int nPiece = 0; nPiece < (caseModel.size - 1) * 4; ++nPiece) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    PieceData pieceData(nPiece, rotation);
                    denyOne(caseInterieur, pieceData, 0, 0);
                }
            }
        }
    }

    CaseData caseCornerLeftTop(0, 0);
    CaseData caseCornerTopRight(caseModel.size - 1, 0);
    CaseData caseCornerRightBot(caseModel.size - 1, caseModel.size - 1);
    CaseData caseCornerBotLeft(0, caseModel.size - 1);

    for (int nPiece = 4; nPiece < pieceModel.piecesQte; ++nPiece) {
        for (int rotation = 0; rotation < 4; ++rotation) {
            PieceData pieceData(nPiece, rotation);

            denyOne(caseCornerLeftTop, pieceData, 0, 0);
            denyOne(caseCornerTopRight, pieceData, 0, 0);
            denyOne(caseCornerRightBot, pieceData, 0, 0);
            denyOne(caseCornerBotLeft, pieceData, 0, 0);

        }
    }

    for (int nPieceCorner = 0; nPieceCorner < 4; ++nPieceCorner) {
        PieceData pieceCornerLeftTop(nPieceCorner, 0);
        denyOne(caseCornerTopRight, pieceCornerLeftTop, 0, 0);
        denyOne(caseCornerRightBot, pieceCornerLeftTop, 0, 0);
        denyOne(caseCornerBotLeft, pieceCornerLeftTop, 0, 0);

        PieceData pieceCornerTopRight(nPieceCorner, 1);
        denyOne(caseCornerLeftTop, pieceCornerTopRight, 0, 0);
        denyOne(caseCornerRightBot, pieceCornerTopRight, 0, 0);
        denyOne(caseCornerBotLeft, pieceCornerTopRight, 0, 0);

        PieceData pieceCornerRightBot(nPieceCorner, 2);
        denyOne(caseCornerLeftTop, pieceCornerRightBot, 0, 0);
        denyOne(caseCornerTopRight, pieceCornerRightBot, 0, 0);
        denyOne(caseCornerBotLeft, pieceCornerRightBot, 0, 0);

        PieceData pieceCornerBotLeft(nPieceCorner, 3);
        denyOne(caseCornerLeftTop, pieceCornerBotLeft, 0, 0);
        denyOne(caseCornerTopRight, pieceCornerBotLeft, 0, 0);
        denyOne(caseCornerRightBot, pieceCornerBotLeft, 0, 0);
    }

}

void CasePieceConstraint::allow(const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth)
{
    // entrypoint : the entrypoint is CasePieceConstraint
    _first.allow(caseData, pieceData, depth); // CaseModel
    _second.allow(caseData, pieceData, depth); // PieceModel

    // entrypoint : advice : comment this if the entrypoint is not this constraint
    while (not eventManager.empty()) {
        eventManager.process();
    }
}

void CasePieceConstraint::denyOne(const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth, const int &persistent)
{
    // doublecheck the deny (can be optimized)
    _first.denyOne(caseData, pieceData, depth, persistent);
    _second.denyOne(caseData, pieceData, depth, persistent);

    // entrypoint : advice : comment this if the entrypoint is not this constraint
    /* // entrypoint : advice : comment this if the entrypoint is not this constraint
    while (not eventManager.empty()) {
        eventManager.process();
    }*/
}

void CasePieceConstraint::deny(const CaseData &caseData,
    const int &depth,
    const int &persistent)
{
    // unused : dangerous : will never be used
    _second.deny(caseData, depth, persistent);
}

void CasePieceConstraint::deny(const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    // unused : dangerous : will never be used
    _first.deny(pieceData, depth, persistent);
}
