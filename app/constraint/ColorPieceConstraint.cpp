#include "ColorPieceConstraint.h"
ColorPieceConstraint::ColorPieceConstraint(ColorModel &colorModel,
    PieceModel &pieceModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(colorModel), _second(pieceModel)
{
    _first.add(*this);
    _second.add(*this);
}

void ColorPieceConstraint::allow(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    //entrypoint : unused : the entrypoint is CasePieceConstraint
    // TODO : minimal importance
    //_first.allow(bordureData, colorData, depth);
    // all the pieces having this color are allowed
    //_second.allow(caseData, pieceData, depth);

    // entrypoint : unused : to be uncommented if the entrypoint is this Constraint
    /* // entrypoint : advice : comment this if the entrypoint is not this constraint
    while(not eventManager.empty()){
        eventManager.process();
    }*/

}

void ColorPieceConstraint::allow(const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth)
{
    // entrypoint : unused : the entrypoint is CasePieceConstraint
    // TODO : minimal importance
}

void ColorPieceConstraint::denyOne(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth, const int &persistent)
{
    //TODO : all the pieces having this color are denied on this two cases (borders)
    //_second.denyOne(caseData, pieceData, depth, persistent);

}

void ColorPieceConstraint::denyOne(const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth, const int &persistent)
{
    //TODO : all the colors of this pieces (four borders) are denied
    // _first.denyOne(bordureData, colorData, depth, persistent)

}

void ColorPieceConstraint::deny(const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // TODO : minimal importance
    // unused : dangerous : won't be used, the effects are too big
}

void ColorPieceConstraint::deny(const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    // TODO
    // unused : dangerous : won't be used, the effects are too big
}
