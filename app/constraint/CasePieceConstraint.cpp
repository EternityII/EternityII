#include "CasePieceConstraint.h"

void CasePieceConstraint::accepted(CaseData &caseData, const int &depth)
{
    // TODO : notify PieceModel that the case is not available anymore
    second->accept(caseData, depth);
}

void CasePieceConstraint::accepted(PieceData &pieceData, const int &depth)
{
    //TODO : notify CaseModel that the piece is not available anymore
    first->accept(pieceData, depth);
}

void CasePieceConstraint::discarded(CaseData &caseData, const int &depth)
{
}

void CasePieceConstraint::discarded(PieceData &pieceData, const int &depth)
{
    //TODO
}

void CasePieceConstraint::rollback(const int &depth)
{
    //TODO
}

void CasePieceConstraint::accept(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    first->accept(caseData, depth); // CaseModel
    second->accept(pieceData, depth); // PieceModel
}

void CasePieceConstraint::discard(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    first->discard(caseData, depth);
    second->discard(pieceData, depth);
}
