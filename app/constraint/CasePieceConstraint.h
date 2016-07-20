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
    void accept(
        const CaseData &caseData, const PieceData &pieceData, const int &depth);

    /**
     * @param CaseData &caseData, the variable to apply
     * @param PieceData &pieceData, the value to apply
     *
     * discards this variable<->value association
     */
    void discard(
        const CaseData &caseData, const PieceData &pieceData, const int &depth);

    /**
     * @param CaseData &pieceData, variable data
     *
     * propagates (applies) the data to PieceModel from CaseModel
     */
    void accepted(const CaseData &caseData, const int &depth);

    /**
     * @param PieceData &pieceData, value data
     *
     * propagates (applies) the data to CaseModel from PieceModel
     */
    void accepted(const PieceData &pieceData, const int &depth);

    void discarded(const PieceData &pieceData, const int &depth);

    void discarded(const CaseData &caseData, const int &depth);
};


#endif //ETERNITYII_CASEPIECECONSTRAINT_H
