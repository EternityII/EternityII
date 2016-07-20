#include "BordureFaceConstraint.h"

BordureFaceConstraint::BordureFaceConstraint(BordureModel &bordureModel,
    FaceModel &faceModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(bordureModel),
      _second(faceModel)
{
    _first.add(*this);
    _second.add(*this);
}

void BordureFaceConstraint::accept(
    const BordureData &bordureData, const FaceData &faceData, const int &depth)
{
    _first.accept(bordureData, faceData, depth); // CaseModel
    _second.accept(bordureData, faceData, depth); // PieceModel

    while (!eventManager.empty()) {
        eventManager.process();
    }
}

void BordureFaceConstraint::accepted(const BordureData &bordureData,
    const int &depth)
{
    _second.accepted(bordureData, depth);
}

void BordureFaceConstraint::accepted(const FaceData &faceData, const int &depth)
{
    _first.accepted(faceData, depth);
}

void BordureFaceConstraint::discard(
    const BordureData &bordureData, const FaceData &faceData, const int &depth)
{
    _first.discard(bordureData, faceData, depth);
    _second.discard(bordureData, faceData, depth);

    while (!eventManager.empty()) {
        eventManager.process();
    }
}

void BordureFaceConstraint::discarded(
    const FaceData &faceData, const int &depth)
{
    _first.discarded(faceData, depth);
}

void BordureFaceConstraint::discarded(
    const BordureData &bordureData, const int &depth)
{
    _second.discarded(bordureData, depth);
}
