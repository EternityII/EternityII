#include "PieceCaseSolver.h"

void PieceCaseSolver::initialize(PathFinder<CaseData, PieceData> &pathFinder,
    ConstraintInterface<CaseModel, PieceModel, CaseData, PieceData> &constraintInterface)
{
    this->pathFinder = &pathFinder;
    this->pieceCaseConstraint = (CasePieceConstraint *) &constraintInterface;
}

void PieceCaseSolver::resolve()
{
    int depth = 0;

    resolve(depth);
}

void PieceCaseSolver::resolve(int &depth)
{
    CaseData *caseData = pathFinder->nextVariable(depth);

    if (caseData->valid) {
        resolve(*caseData, depth);
    }

    delete caseData;
}

void PieceCaseSolver::resolve(CaseData &caseData, int &depth)
{
    while (pathFinder->hasNextValue(caseData)) {

        PieceData *pieceData = pathFinder->nextValue(caseData);

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
