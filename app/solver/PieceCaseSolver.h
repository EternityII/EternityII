#ifndef ETERNITYII_DEFAULTSOLVER_H
#define ETERNITYII_DEFAULTSOLVER_H

#include "../../core/SolverInterface.h"
#include "../data/variable/CaseVariableData.h"
#include "../data/value/PieceValueData.h"
#include "../PieceCaseConstraint.h"

class PieceCaseSolver: public SolverInterface
{
public:

    void initialize(PathFinder &pathFinder, ConstraintInterface &constraintInterface);

    /**
     * Begin the resolution process
     */
    void resolve();

private:
    PathFinder *pathFinder;

    PieceCaseConstraint *pieceCaseConstraint;

    /**
     * Recursive resolution method
     */
    void resolve(int &depth);

    void resolve(CaseVariableData &caseVariableData, int &depth);

    bool isValid(PieceValueData &caseVariableData);

    bool isValid(CaseVariableData &caseVariableData);
};


#endif //ETERNITYII_DEFAULTSOLVER_H
