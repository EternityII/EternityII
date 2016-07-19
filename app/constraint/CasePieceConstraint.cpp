#include "CasePieceConstraint.h"

CasePieceConstraint::CasePieceConstraint(CaseModel &caseModel, PieceModel &pieceModel, EventManager &eventManager)
    : ConstraintInterface(eventManager)
{
    this->_first = &caseModel;
    this->_second = &pieceModel;
    _first->add(*this);
    _second->add(*this);

    for (int variable = 1; variable < caseModel.size - 1; ++variable) {
        CaseData caseXBeginEdge(0, variable);
        CaseData caseXEndEdge(caseModel.size - 1, variable);
        CaseData caseYBeginEdge(variable, 0);
        CaseData caseYEndEdge(variable, caseModel.size - 1);

        // interior piece cannot be put on a edge case
        for (int nInsidePiece = (caseModel.size - 1) * 4; nInsidePiece < pieceModel.nbPieces;
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
        for (int nBordPiece = 4; nBordPiece < (caseModel.size - 1) * 4;
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
    for (int x = 1; x < caseModel.size - 1; ++x) {
        for (int y = 1; y < caseModel.size - 1; ++y) {
            CaseData caseInterieur(x, y);
            for (int nPiece = 0; nPiece < (caseModel.size - 1) * 4; ++nPiece) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    PieceData pieceData(nPiece, rotation);
                    discard(caseInterieur, pieceData, 0);
                }
            }
        }
    }

    CaseData caseCornerLeftTop(0, 0);
    CaseData caseCornerTopRight(caseModel.size - 1, 0);
    CaseData caseCornerRightBot(caseModel.size - 1, caseModel.size - 1);
    CaseData caseCornerBotLeft(0, caseModel.size - 1);

    for (int nPiece = 4; nPiece < pieceModel.nbPieces; ++nPiece) {
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

void CasePieceConstraint::accepted(CaseData &caseData, const int &depth)
{
    // notify PieceModel that the case is not available anymore
    _second->accepted(caseData, depth);
}

void CasePieceConstraint::accepted(PieceData &pieceData, const int &depth)
{
    // notify CaseModel that the piece is not available anymore
    _first->accepted(pieceData, depth);
}

void CasePieceConstraint::accept(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    _first->accept(caseData, depth); // CaseModel
    _second->accept(pieceData, depth); // PieceModel

    while (!eventManager->empty()) {
        eventManager->process();
    }
}

void CasePieceConstraint::discard(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    _first->discard(caseData, pieceData, depth);
    _second->discard(caseData, pieceData, depth);

    while (!eventManager->empty()) {
        eventManager->process();
    }
}

void CasePieceConstraint::discarded(CaseData &caseData, const int &depth)
{
    _second->discarded(caseData, depth);
}
void CasePieceConstraint::discarded(PieceData &pieceData, const int &depth)
{
    _first->discarded(pieceData, depth);
}
