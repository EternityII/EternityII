#ifndef ETERNITYII_DEFAULTSOLVER_H
#define ETERNITYII_DEFAULTSOLVER_H

#include <iostream>
#include <algorithm>

#include "../../core/SolverInterface.h"
#include "../constraint/CasePieceConstraint.h"

using namespace std;

class CasePieceSolver: public SolverInterface
{
private:
    CasePieceConstraint &_constraint;

    vector<vector<PieceData>> plateau;

    clock_t durationVariable = 0;
    clock_t durationValue = 0;
    clock_t durationAllow = 0;
    clock_t durationDeny = 0;
    clock_t durationRollback = 0;
    clock_t durationPartialRollback = 0;

    long long quantityNodes = 0;
    vector<long> quantityNodesByDepth;
    long long quantityVariables = 0;
    long long quantityValues = 0;
    int quantitySolutions = 0;
    long long quantityNodesFirstSolution = 0;

    int maxDepth;

    int size;

    /**
     * Recursive resolution method
     */
    void resolve(int &depth);

    void resolve(CaseData &caseData, int &depth);
    bool isPossible(const CaseData &caseData, const PieceData &pieceData) const;
    void putPiece(const CaseData &caseData, const PieceData &pieceData);

    void popPiece(const CaseData &caseData, const PieceData &pieceData);
    bool isBorderFalse(const CaseData &caseData,
        const PieceData &pieceData,
        const int border) const;

public:

    CasePieceSolver(PathFinder &pathFinder,
        ConstraintInterface &constraintInterface,
        vector<unique_ptr<ModelInterface>> &models,
        GameImportData &gameImportData);

    /**
     * Begin the resolution process
     */
    void resolve();
    void firstOpti();
};


#endif //ETERNITYII_DEFAULTSOLVER_H
