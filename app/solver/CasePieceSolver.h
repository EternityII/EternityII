#ifndef ETERNITYII_DEFAULTSOLVER_H
#define ETERNITYII_DEFAULTSOLVER_H

#include <iostream>
#include "../../core/SolverInterface.h"
#include "../constraint/CasePieceConstraint.h"

using namespace std;

class CasePieceSolver: public SolverInterface
{
public:

    CasePieceSolver(PathFinder &pathFinder,
        ConstraintInterface &constraintInterface,
        vector<unique_ptr<ModelInterface>> &models,
        GameImportData &gameImportData);

    /**
     * Begin the resolution process
     */
    void resolve();

private:
    CasePieceConstraint *_constraint;

    vector<vector<PieceData>> plateau;

    /**
     * Recursive resolution method
     */
    void resolve(int &depth);

    void resolve(CaseData &caseData, int &depth);

    bool isPossible(CaseData &caseData, PieceData &pieceData);
    void putPiece(CaseData &caseData, PieceData &pieceData);
    void popPiece(CaseData &caseData, PieceData &pieceData);

    bool isBorderFalse(const CaseData &caseData,
        const PieceData &pieceData,
        const int border) const;
};


#endif //ETERNITYII_DEFAULTSOLVER_H
