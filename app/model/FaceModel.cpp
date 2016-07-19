#include "FaceModel.h"
FaceModel::FaceModel(GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{

}

void FaceModel::accept(FaceData &faceData, const int &depth)
{

}

void FaceModel::accepted(BordureData &bordureData, const int &depth)
{

}

void FaceModel::accepted(PieceData &pieceData, const int &depth)
{

}

void FaceModel::discard(
    BordureData &bordureData, FaceData &faceData, const int &depth
)
{

}

void FaceModel::discarded(FaceData &faceData, const int &depth)
{

}
