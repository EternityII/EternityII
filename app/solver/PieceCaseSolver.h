#ifndef ETERNITYII_DEFAULTSOLVER_H
#define ETERNITYII_DEFAULTSOLVER_H

#include <iostream>
#include "../../core/SolverInterface.h"
#include "../constraint/CasePieceConstraint.h"

using namespace std;

class PieceCaseSolver: public SolverInterface<CaseModel, PieceModel, CaseData, PieceData>
{
public:

    void initialize(PathFinder<CaseData, PieceData> &pathFinder,
        ConstraintInterface<CaseModel, PieceModel, CaseData, PieceData> &constraintInterface);

    /**
     * Begin the resolution process
     */
    void resolve();

private:
    PathFinder<CaseData, PieceData> *pathFinder;

    CasePieceConstraint *pieceCaseConstraint;

    /**
     * Recursive resolution method
     */
    void resolve(int &depth);

    void resolve(CaseData &caseData, int &depth);

};


#endif //ETERNITYII_DEFAULTSOLVER_H
