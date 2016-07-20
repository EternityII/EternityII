#include "FacePieceConstraint.h"
FacePieceConstraint::FacePieceConstraint(FaceModel &faceModel,
    PieceModel &pieceModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(faceModel), _second(pieceModel)
{
    _first.add(*this);
    _second.add(*this);
}
void FacePieceConstraint::accept(const FaceData &faceData,
    const PieceData &pieceData,
    const int &depth)
{
    // TODO
}

void FacePieceConstraint::discard(const FaceData &faceData,
    const PieceData &pieceData,
    const int &depth)
{
    // TODO
}

void FacePieceConstraint::accepted(const FaceData &faceData, const int &depth)
{
    // TODO
}

void FacePieceConstraint::accepted(const PieceData &pieceData, const int &depth)
{
    // TODO
}

void FacePieceConstraint::discarded(const PieceData &pieceData,
    const int &depth)
{
    // TODO
}
void FacePieceConstraint::discarded(const FaceData &faceData, const int &depth)
{
    // TODO
}
