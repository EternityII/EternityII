#include "FacePiececonstraint.h"
FacePiececonstraint::FacePiececonstraint(FaceModel &faceModel,
    PieceModel &pieceModel,
    EventManager &eventManager)
    : ConstraintInterface(eventManager), _first(faceModel), _second(pieceModel)
{
    _first.add(*this);
    _second.add(*this);
}
void FacePiececonstraint::accept(const FaceData &faceData,
    const PieceData &pieceData,
    const int &depth)
{
    // TODO
}

void FacePiececonstraint::discard(const FaceData &faceData,
    const PieceData &pieceData,
    const int &depth)
{
    // TODO
}

void FacePiececonstraint::accepted(const FaceData &faceData, const int &depth)
{
    // TODO
}

void FacePiececonstraint::accepted(const PieceData &pieceData, const int &depth)
{
    // TODO
}

void FacePiececonstraint::discarded(const PieceData &pieceData,
    const int &depth)
{
    // TODO
}
void FacePiececonstraint::discarded(const FaceData &faceData, const int &depth)
{
    // TODO
}
