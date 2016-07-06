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
        ConstraintInterface &constraintInterface,
        vector<unique_ptr<ModelInterface>> &models,
        GameImportData &gameImportData);

    /**
     * Begin the resolution process
     */
    void resolve();

private:
    PathFinder *pathFinder;

    vector<unique_ptr<ModelInterface>> *models;

    CasePieceConstraint *pieceCaseConstraint;

    GameImportData *game;

    vector<vector<vector<int>>> plateau;

    /**
     * Recursive resolution method
     */
    void resolve(int &depth);

    void resolve(CaseData &caseData, int &depth);

    bool isPossible(CaseData &data, PieceData &pieceData);
    void putPiece(CaseData &data, PieceData &pieceData);
    void popPiece(CaseData &data, PieceData &pieceData);
};


#endif //ETERNITYII_DEFAULTSOLVER_H
