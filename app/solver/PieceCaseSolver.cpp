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
    //Exist in this scope
    unique_ptr<DataInterface> dataptr = move(pathFinder->nextVariable(depth));
    // Casted to use it
    CaseData *caseData = (CaseData *) dataptr.get();

    if (caseData->valid) {
        resolve(*caseData, depth);
    }
}

void PieceCaseSolver::resolve(CaseData &caseData, int &depth)
{
    // Existance of the data
    unique_ptr<DataInterface> dataptr = move(pathFinder->nextValue(caseData));
    // Casted to use it
    PieceData *pieceData = (PieceData *) dataptr.get();

    // TODO LOGIC
    if (pieceData->valid) {
        pieceCaseConstraint->accept(caseData, *pieceData, depth);
        ++depth;
        cout << depth << endl;
        resolve(depth);
        --depth;
        pieceCaseConstraint->rollback(depth);
        pieceCaseConstraint->discard(caseData, *pieceData, depth);
    }
}
