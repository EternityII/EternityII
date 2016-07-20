#include "FaceModel.h"
FaceModel::FaceModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    //TODO
}

void FaceModel::accept(
    const BordureData &bordureData, const FaceData &faceData, const int &depth)
{
    //TODO
}

void FaceModel::accepted(const BordureData &bordureData, const int &depth)
{
    //TODO
}

void FaceModel::accepted(const PieceData &pieceData, const int &depth)
{
    //TODO
}

void FaceModel::discard(
    const BordureData &bordureData, const FaceData &faceData, const int &depth)
{
    //TODO
}

void FaceModel::discarded(const BordureData &bordureData, const int &depth)
{
    //TODO
}

void FaceModel::rollback(const int &depth, const bool total)
{
    //TODO
}
