#ifndef ETERNITYII_CASEPIECECONSTRAINT_H
#define ETERNITYII_CASEPIECECONSTRAINT_H

#include "../../core/ConstraintInterface.h"
#include "../model/CaseModel.h"
#include "../model/PieceModel.h"

class CasePieceConstraint: public ConstraintInterface<CaseModel, PieceModel, CaseData, PieceData>
{
public:
    /**
     * @param CaseData &caseData, the variable to apply
     * @param PieceData &pieceData, the value to apply
     *
     * applies the data for this constraint
     */
    void accept(CaseData &caseData, PieceData &pieceData, const int &depth);

    /**
     * @param CaseData &caseData, the variable to apply
     * @param PieceData &pieceData, the value to apply
     *
     * discards this variable<->value association
     */
    void discard(CaseData &caseData, PieceData &pieceData, const int &depth);

    /**
     * @param CaseData &pieceData, variable data
     *
     * propagates (applies) the data to PieceModel from CaseModel
     */
    void accepted(CaseData &caseData, const int &depth);

    /**
     * @param PieceData &pieceData, value data
     *
     * propagates (applies) the data to CaseModel from PieceModel
     */
    void accepted(PieceData &pieceData, const int &depth);

    /**
     * @param CaseData &caseData, variable data
     *
     * propagates (applies) the data to PieceModel from CaseModel
     */
    void discarded(CaseData &caseData, const int &depth);

    /**
     * @param PieceData &pieceData, value data
     *
     * propagates (discards) the data to CaseModel from PieceModel
     */
    void discarded(PieceData &pieceData, const int &depth);

    /**
     * @param  int const &depth
     *
     * Rollback the table to depth
     */
    void rollback(const int &depth);
};


#endif //ETERNITYII_CASEPIECECONSTRAINT_H
