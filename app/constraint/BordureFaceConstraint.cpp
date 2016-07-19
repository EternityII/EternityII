#include "BordureFaceConstraint.h"
BordureFaceConstraint::BordureFaceConstraint(
    BordureModel &bordureModel, FaceModel &faceModel, EventManager &eventManager
)
    : ConstraintInterface(eventManager)
{

}

void BordureFaceConstraint::accept(
    BordureData &bordureData, FaceData &faceData, const int &depth)
{

}

void BordureFaceConstraint::discard(
    BordureData &bordureData, FaceData &faceData, const int &depth)
{

}

void BordureFaceConstraint::accepted(BordureData &bordureData, const int &depth)
{

}

void BordureFaceConstraint::accepted(FaceData &faceData, const int &depth)
{

}

void BordureFaceConstraint::discarded(FaceData &faceData, const int &depth)
{

}

void BordureFaceConstraint::discarded(
    BordureData &bordureData, const int &depth)
{

}
