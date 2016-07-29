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
    // entrypoint : unused : the entrypoint is CasePieceConstraint
    _first.allow(bordureData, colorData, depth); // CaseModel
    _second.allow(bordureData, colorData, depth); // PieceModel

    // entrypoint : unused : to be uncommented if the entrypoint is this Constraint
    /* // entrypoint : advice : comment this if the entrypoint is not this constraint
    while (not eventManager.empty()) {
        eventManager.process();
    }*/
}

void BordureColorConstraint::denyOne(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // doublechecking each time (blocked by if) can be optimized
    _first.denyOne(bordureData, colorData, depth, persistent);
    _second.denyOne(bordureData, colorData, depth, persistent);
}

void BordureColorConstraint::addOne(
    const BordureData &bordureData,
    const ColorData &colorData)
{
    // entrypoint : unused : never called because the entrypoint is CasePieceConstraint
    /*
    _first.addOne(bordureData, colorData);
    _second.addOne(bordureData, colorData);
    */
}

void BordureColorConstraint::deny(
    const BordureData &bordureData, const int &depth, const int &persistent)
{
    // unused : dangerous : use with care
    _second.deny(bordureData, depth, persistent);
}

void BordureColorConstraint::deny(const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // unused : dangerous : use with care
    _first.deny(colorData, depth, persistent);
}
