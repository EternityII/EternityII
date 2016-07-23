#ifndef ETERNITYII_BORDURECASECONSTRAINT_H
#define ETERNITYII_BORDURECASECONSTRAINT_H

#include "../../core/ConstraintInterface.h"
#include "../model/BordureModel.h"
#include "../model/CaseModel.h"

class BordureCaseConstraint: public ConstraintInterface
{
    BordureModel &_first;
    CaseModel &_second;
public:
    BordureCaseConstraint(BordureModel &bordureModel,
        CaseModel &caseModel,
        EventManager &eventManager);

    void allow(
        const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth);

    void allow(
        const CaseData &caseData, const PieceData &pieceData, const int &depth);

    void denyOne(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth,
        const int &persistent);

    void denyOne(const CaseData &caseData,
        const PieceData &pieceData,
        const int &depth,
        const int &persistent);

    void deny(const BordureData &bordureData,
        const int &depth,
        const int &persistent);

    void deny(
        const CaseData &caseData, const int &depth, const int &persistent);
};


#endif //ETERNITYII_BORDURECASECONSTRAINT_H
