#ifndef ETERNITYII_PIECECASECONSTRAINT_H
#define ETERNITYII_PIECECASECONSTRAINT_H


#include "../core/ConstraintInterface.h"
#include "model/PieceModel.h"
#include "model/CaseModel.h"
#include "data/variable/CaseVariableData.h"
#include "data/value/PieceValueData.h"


class PieceCaseConstraint: public ConstraintInterface
{
protected:
    PieceModel *first;
    CaseModel *second;
public:
    void accept(CaseVariableData &caseVariableData, PieceValueData &pieceValueData, const int &depth);

    void discard(CaseVariableData &caseVariableData, PieceValueData &pieceValueData, const int &depth);

    void accepted(CaseVariableData &caseVariableData);

    void accepted(PieceValueData &pieceValueData);

    void discarded(CaseVariableData &caseVariableData);

    void discarded(PieceValueData &pieceValueData);

    void rollback(const int &depth);
};


#endif //ETERNITYII_PIECECASECONSTRAINT_H
