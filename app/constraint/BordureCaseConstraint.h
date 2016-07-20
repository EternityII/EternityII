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

    /**
     * @param BordureData &bordureData, the variable to apply
     * @param CaseData &caseData, the value to apply
     *
     * applies the data for this constraint
     */
    void accept(const BordureData &bordureData,
        const CaseData &caseData,
        const int &depth);

    /**
     * @param BordureData &bordureData, the variable to apply
     * @param CaseData &caseData, the value to apply
     *
     * discards this variable<->value association
     */
    void discard(const BordureData &bordureData,
        const CaseData &caseData,
        const int &depth);

    /**
     * @param BordureData &caseData, variable data
     *
     * propagates (applies) the data to FaceModel from BordureModel
     */
    void accepted(const BordureData &bordureData, const int &depth);

    /**
     * @param CaseData &caseData, value data
     *
     * propagates (applies) the data to BordureModel from FaceModel
     */
    void accepted(const CaseData &caseData, const int &depth);

    void discarded(const CaseData &caseData, const int &depth);

    void discarded(const BordureData &bordureData, const int &depth);
};


#endif //ETERNITYII_BORDURECASECONSTRAINT_H
