#include "CasePieceConstraint.h"

CasePieceConstraint::CasePieceConstraint(CaseModel &caseModel,
    PieceModel &pieceModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(caseModel), _second(pieceModel)
{
    _first.add(*this);
    _second.add(*this);
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
    while (not eventManager.empty()) {
        eventManager.process();
    }
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
