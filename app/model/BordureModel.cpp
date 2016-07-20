#include "BordureModel.h"

BordureModel::BordureModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    //TODO
}

void BordureModel::accept(
    const BordureData &bordureData, const FaceData &faceData, const int &depth)
{
    //TODO
}

void BordureModel::accepted(const FaceData &faceData, const int &depth)
{
    //TODO
}

void BordureModel::accepted(const CaseData &caseData, const int &depth)
{
    //TODO
}

void BordureModel::discard(
    const BordureData &bordureData, const FaceData &faceData, const int &depth
)
{
    //TODO
}

void BordureModel::discarded(const FaceData &faceData, const int &depth)
{
    //TODO
}

void BordureModel::rollback(const int &depth, const bool total/* = true */)
{
    //TODO
}
