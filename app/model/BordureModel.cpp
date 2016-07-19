#include "BordureModel.h"

BordureModel::BordureModel(GameImportData &gameImportData,
    EventManager &eventManager)
    : ModelInterface(eventManager)
{

}

void BordureModel::accept(BordureData &bordureData, const int &depth)
{

}

void BordureModel::accepted(FaceData &faceData, const int &depth)
{

}

void BordureModel::accepted(CaseData &caseData, const int &depth)
{

}

void BordureModel::discard(
    BordureData &bordureData, FaceData &faceData, const int &depth
)
{

}

void BordureModel::discarded(FaceData &faceData, const int &depth)
{

}

void BordureModel::rollback(const int &depth, const bool total/* = true */)
{

}
