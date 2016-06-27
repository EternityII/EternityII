#include "PieceCaseConstraint.h"

void PieceCaseConstraint::accepted(CaseData &caseData)
{
    //TODO
}

void PieceCaseConstraint::accepted(PieceData &pieceData)
{
    //TODO
}

void PieceCaseConstraint::discarded(CaseData &caseData)
{
    //TODO
}

void PieceCaseConstraint::discarded(PieceData &pieceData)
{
    //TODO
}

void PieceCaseConstraint::rollback(const int &depth)
{
    //TODO
}

void PieceCaseConstraint::accept(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    //first->accept(pieceData, depth);
    second->accept(caseData, depth);
}

void PieceCaseConstraint::discard(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    first->discard(pieceData, depth);
    second->discard(caseData, depth);
}
