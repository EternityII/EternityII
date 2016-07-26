#include "BordureColorConstraint.h"

BordureColorConstraint::BordureColorConstraint(BordureModel &bordureModel,
    ColorModel &colorModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(bordureModel),
      _second(colorModel)
{
    _first.add(*this);
    _second.add(*this);
}

void BordureColorConstraint::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    _first.allow(bordureData, colorData, depth); // CaseModel
    _second.allow(bordureData, colorData, depth); // PieceModel

    // the entry point is CasePieceConstraint
    /* while (!eventManager.empty()) {
        eventManager.process();
    }*/
}

void BordureColorConstraint::denyOne(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // yep
    _first.denyOne(bordureData, colorData, depth, persistent);
    _second.denyOne(bordureData, colorData, depth, persistent);

    // the entry point is CasePieceConstraint
    /* while (!eventManager.empty()) {
        eventManager.process();
    }*/
}

void BordureColorConstraint::deny(
    const BordureData &bordureData, const int &depth, const int &persistent)
{
    _second.deny(bordureData, depth, persistent);
}

void BordureColorConstraint::deny(const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    _first.deny(colorData, depth, persistent);
}
