#include "CasePieceSolver.h"

void CasePieceSolver::initialize(PathFinder &pathFinder,
    ConstraintInterface &constraintInterface)
{
    this->pathFinder = &pathFinder;
    this->pieceCaseConstraint = dynamic_cast<CasePieceConstraint *>(&constraintInterface);
}

void CasePieceSolver::resolve()
{
    int depth = 0;

    resolve(depth);
}

void CasePieceSolver::resolve(int &depth)
{
    CaseData *caseData = static_cast<CaseData *>(pathFinder->nextVariable(depth));

    if (caseData->valid) {
        resolve(*caseData, depth);
    }

    delete caseData;
}

void CasePieceSolver::resolve(CaseData &caseData, int &depth)
{
    while (pathFinder->hasNextValue(caseData)) {

        PieceData *pieceData = static_cast<PieceData *>(pathFinder->nextValue(caseData));

        if (pieceData->valid) {
            pieceCaseConstraint->accept(caseData, *pieceData, depth);
            ++depth;
            cout << depth << endl;
            resolve(depth);
            --depth; // end of recursivity, rolling back to depth
            pieceCaseConstraint->rollback(depth);
            pieceCaseConstraint->discard(caseData, *pieceData, depth);
        }

        delete pieceData;
    }
}
