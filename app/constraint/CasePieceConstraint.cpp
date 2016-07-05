#include "CasePieceConstraint.h"

void CasePieceConstraint::accepted(CaseData &caseData, const int &depth)
{
    // TODO : notify PieceModel that the case is not available anymore
    _second->accepted(caseData, depth);
}

void CasePieceConstraint::accepted(PieceData &pieceData, const int &depth)
{
    //TODO : notify CaseModel that the piece is not available anymore
    _first->accept(pieceData, depth);
}

void CasePieceConstraint::discarded(CaseData &caseData, const int &depth)
{
    _first->discard(caseData, depth);
}

void CasePieceConstraint::discarded(PieceData &pieceData, const int &depth)
{
    _first->discard(pieceData, depth);
}

void CasePieceConstraint::rollback(const int &depth)
{
    //TODO
}

void CasePieceConstraint::accept(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    _first->accept(caseData, depth); // CaseModel
    _second->accept(pieceData, depth); // PieceModel
}

void CasePieceConstraint::discard(CaseData &caseData, PieceData &pieceData, const int &depth)
{
    _first->discard(caseData, depth);
    _second->discard(pieceData, depth);
}
void CasePieceConstraint::setFirst(CaseModel &modelInterface)
{
    this->_first =  &modelInterface;

    _first->add(*this);
}
void CasePieceConstraint::setSecond(PieceModel &modelInterface)
{
    this->_second = &modelInterface;

    _second->add(*this);
}