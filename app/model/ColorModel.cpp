#include "ColorModel.h"
ColorModel::ColorModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    //TODO
}

void ColorModel::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    //TODO
}

void ColorModel::denyOne(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    //TODO
}

void ColorModel::deny(const BordureData &bordureData,
    const int &depth,
    const int &persistent)
{
    //TODO
}

void ColorModel::deny(const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    //TODO

}

void ColorModel::rollback(const int &depth, const bool total)
{
    //TODO
}
