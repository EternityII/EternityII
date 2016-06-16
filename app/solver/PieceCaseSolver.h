#ifndef ETERNITYII_DEFAULTSOLVER_H
#define ETERNITYII_DEFAULTSOLVER_H

#include "../../core/SolverInterface.h"
#include "../data/variable/CaseData.h"
#include "../data/value/PieceData.h"
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

    void resolve(CaseData &caseData, int &depth);

};


#endif //ETERNITYII_DEFAULTSOLVER_H
