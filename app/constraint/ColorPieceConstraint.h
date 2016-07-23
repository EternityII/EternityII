#ifndef ETERNITYII_COLORPIECECONSTRAINT_H
#define ETERNITYII_COLORPIECECONSTRAINT_H


#include "../../core/ConstraintInterface.h"
#include "../model/ColorModel.h"
#include "../model/PieceModel.h"

class ColorPieceConstraint: public ConstraintInterface
{
    ColorModel &_first;
    PieceModel &_second;
public:
    ColorPieceConstraint(ColorModel &colorModel,
        PieceModel &pieceModel,
        EventManager &eventManager);

    void allow(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth);

    void allow(const CaseData &caseData,
        const PieceData &pieceData,
        const int &depth);

    void denyOne(
        const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth, const int &persistent);

    void denyOne(
        const CaseData &caseData,
        const PieceData &pieceData,
        const int &depth,
        const int &persistent);

    void deny(
        const ColorData &colorData, const int &depth, const int &persistent);

    void deny(
        const PieceData &pieceData, const int &depth, const int &persistent);
};


#endif //ETERNITYII_COLORPIECECONSTRAINT_H
