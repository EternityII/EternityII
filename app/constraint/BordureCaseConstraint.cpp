#include "BordureCaseConstraint.h"
BordureCaseConstraint::BordureCaseConstraint(BordureModel &bordureModel,
    CaseModel &caseModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(bordureModel),
      _second(caseModel)
{
    _first.add(*this);
    _second.add(*this);
}

void BordureCaseConstraint::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    // TODO : Adapt
    //_first.allow(bordureData, colorData, depth);
    //_second.allow(caseData, bordureData, depth);
}

void BordureCaseConstraint::allow(
    const CaseData &caseData, const PieceData &pieceData, const int &depth)
{
    // TODO : Adapt
    //_first.allow(bordureData, colorData, depth);
    //_second.allow(caseData, bordureData, depth);
}

void BordureCaseConstraint::denyOne(
    const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    // TODO : adapt
    // _first.denyOne(bordureData, colorData,depth,persistent);
}

void BordureCaseConstraint::denyOne(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // TODO : adapt
    //_second.denyOne(caseData, pieceData, depth, persistent);

}

void BordureCaseConstraint::deny(
    const BordureData &bordureData, const int &depth, const int &persistent)
{
    //TODO :
    //_second.deny(caseData,depth)
}

void BordureCaseConstraint::deny(
    const CaseData &caseData, const int &depth, const int &persistent)
{
    //TODO
    //_first.deny(bordureData,depth);
}
