#ifndef ETERNITYII_COLORMODEL_H
#define ETERNITYII_COLORMODEL_H


#include "../../core/model/ModelInterface.h"
#include "BordureModel.h"
#include "../data/variable/BordureData.h"
#include "../data/value/PieceData.h"

class ColorModel: public ModelInterface
{
public:
    ColorModel(const GameImportData &gameImportData,
        EventManager &eventManager);

    void allow(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth);

    void denyOne(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth, const int &persistent);

    void deny(const BordureData &bordureData,
        const int &depth,
        const int &persistent);

    void deny(const ColorData &colorData,
        const int &depth,
        const int &persistent);

    void rollback(const int &depth, const bool total = true);
};


#endif //ETERNITYII_COLORMODEL_H
