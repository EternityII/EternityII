#ifndef ETERNITYII_DEFAULTSOLVER_H
#define ETERNITYII_DEFAULTSOLVER_H

#include <iostream>
#include "../../core/SolverInterface.h"
#include "../constraint/CasePieceConstraint.h"

using namespace std;

class CasePieceSolver: public SolverInterface
{
public:

    void initialize(PathFinder &pathFinder,
        ConstraintInterface &constraintInterface);

    /**
     * Begin the resolution process
     */
    void resolve();

private:
    PathFinder *pathFinder;

    CasePieceConstraint *pieceCaseConstraint;

    /**
     * Recursive resolution method
     */
    void resolve(int &depth);

    void resolve(CaseData &caseData, int &depth);

};


#endif //ETERNITYII_DEFAULTSOLVER_H
