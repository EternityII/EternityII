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
    //TODO:

}

void ColorPieceConstraint::allow(const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth)
{
    //TODO:
}

void ColorPieceConstraint::denyOne(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth, const int &persistent)
{
    //TODO:

}

void ColorPieceConstraint::denyOne(const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth, const int &persistent)
{
    //TODO:

}

void ColorPieceConstraint::deny(const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // TODO
}

void ColorPieceConstraint::deny(const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    // TODO
}
