#ifndef ETERNITYII_PIECECASECONSTRAINT_H
#define ETERNITYII_PIECECASECONSTRAINT_H


#include "../../core/ConstraintInterface.h"
#include "../model/PieceModel.h"
#include "../model/CaseModel.h"
#include "../data/variable/CaseData.h"
#include "../data/value/PieceData.h"


class PieceCaseConstraint: public ConstraintInterface
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
    void accepted(CaseData &caseData);

    /**
     * @param PieceData &pieceData, value data
     *
     * propagates (applies) the data to CaseModel from PieceModel
     */
    void accepted(PieceData &pieceData);

    /**
     * @param CaseData &caseData, variable data
     *
     * propagates (applies) the data to PieceModel from CaseModel
     */
    void discarded(CaseData &caseData);

    /**
     * @param PieceData &pieceData, value data
     *
     * propagates (discards) the data to CaseModel from PieceModel
     */
    void discarded(PieceData &pieceData);

    /**
     * @param  int const &depth
     *
     * Rollback the table to depth
     */
    void rollback(const int &depth);
};


#endif //ETERNITYII_PIECECASECONSTRAINT_H
