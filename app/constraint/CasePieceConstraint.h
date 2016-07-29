#ifndef ETERNITYII_CASEPIECECONSTRAINT_H
#define ETERNITYII_CASEPIECECONSTRAINT_H

#include "../../core/ConstraintInterface.h"
#include "../model/CaseModel.h"
#include "../model/PieceModel.h"

class CasePieceConstraint: public ConstraintInterface
{
    CaseModel &_first;
    PieceModel &_second;
public:
    CasePieceConstraint(CaseModel &caseModel,
        PieceModel &pieceModel,
        EventManager &eventManager);

    /**
     * @param CaseData &caseData, the variable to apply
     * @param PieceData &pieceData, the value to apply
     *
     * applies the data for this constraint
     */
    void allow(
        const CaseData &caseData, const PieceData &pieceData, const int &depth);

    void addOne(const CaseData &caseData, const PieceData &pieceData);

    /**
     * @param CaseData &caseData, the variable to apply
     * @param PieceData &pieceData, the value to apply
     *
     * denys this variable<->value association
     */
    void denyOne(
        const CaseData &caseData,
        const PieceData &pieceData,
        const int &depth,
        const int &persistent);

    void
    deny(const PieceData &pieceData, const int &depth, const int &persistent);

    void
    deny(const CaseData &caseData, const int &depth, const int &persistent);
};


#endif //ETERNITYII_CASEPIECECONSTRAINT_H
