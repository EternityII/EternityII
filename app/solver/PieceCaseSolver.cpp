#include "PieceCaseSolver.h"

void PieceCaseSolver::initialize(PathFinder &pathFinder, ConstraintInterface &constraintInterface)
{
    this->pathFinder = &pathFinder;
    this->pieceCaseConstraint = (PieceCaseConstraint *) &constraintInterface;
}

void PieceCaseSolver::resolve()
{
    int depth = 0;

    resolve(depth);
}

void PieceCaseSolver::resolve(int &depth)
{
    CaseData *caseData = static_cast<CaseData *>(pathFinder->nextVariable(depth));

    if (caseData->valid) {
        resolve(*caseData, depth);
    }

    delete caseData;
}

void PieceCaseSolver::resolve(CaseData &caseData, int &depth)
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
