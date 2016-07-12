#include "CasePieceConstraint.h"

CasePieceConstraint::CasePieceConstraint(CaseModel &caseModel, PieceModel &pieceModel, EventManager &eventManager)
    : ConstraintInterface(eventManager)
{
    this->_first = &caseModel;
    this->_second = &pieceModel;
    _first->add(*this);
    _second->add(*this);

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

void CasePieceConstraint::rollback(const int &from, const int &to)
{
    // nothing to do, not used
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
