#ifndef ETERNITYII_BORDURECOLORCONSTRAINT_H
#define ETERNITYII_BORDURECOLORCONSTRAINT_H

#include "../../core/ConstraintInterface.h"
#include "../model/BordureModel.h"
#include "../model/ColorModel.h"

class BordureColorConstraint: public ConstraintInterface
{
    BordureModel &_first;
    ColorModel &_second;
public:
    BordureColorConstraint(BordureModel &bordureModel,
        ColorModel &colorModel,
        EventManager &eventManager);

    void allow(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth);

    void addOne(const BordureData &bordureData, const ColorData &colorData);

    void denyOne(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth,
        const int &persistent);

    void deny(const BordureData &bordureData,
        const int &depth,
        const int &persistent);

    void deny(const ColorData &colorData,
        const int &depth,
        const int &persistent);

};


#endif //ETERNITYII_BORDURECOLORCONSTRAINT_H
