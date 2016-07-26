#include "BordureCaseConstraint.h"
BordureCaseConstraint::BordureCaseConstraint(BordureModel &bordureModel,
    CaseModel &caseModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(bordureModel),
      _second(caseModel)
{
    _first.add(*this);
    _second.add(*this);

    // TODO all the equivalence piece[rotation].id <--> colors.id and bordure.id <--> case.id
}

void BordureCaseConstraint::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{

    /* TODO : INACTIVE : entrypoint */
    //_first.allow(bordureData, colorData, depth);
    // TODO : all the four borders are denied
    //_second.allow(caseData, pieceData, depth);
}

void BordureCaseConstraint::allow(
    const CaseData &caseData, const PieceData &pieceData, const int &depth)
{
    /* TODO : INACTIVE : entrypoint */
    //_first.allow(bordureData, colorData, depth);
    // TODO : all the four borders are denied
    //_second.allow(caseData, bordureData, depth);
}

void BordureCaseConstraint::denyOne(
    const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    // TODO : all four borders of the case have one less occurence of the piececolor
    // _first.denyOne(bordureData, colorData,depth,persistent);
}

void BordureCaseConstraint::denyOne(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // one border has 2 cases
    // todo : all the pieces containing colors are not allowed on the cases contianing this border
    //_second.denyOne(caseData, pieceData, depth, persistent);

}

void BordureCaseConstraint::deny(
    const BordureData &bordureData, const int &depth, const int &persistent)
{
    //TODO : certainly not used, minimal priority
    //_second.deny(caseData,depth)
}

void BordureCaseConstraint::deny(
    const CaseData &caseData, const int &depth, const int &persistent)
{
    //TODO : certainly not used, minimal priority
    //_first.deny(bordureData,depth);
}
