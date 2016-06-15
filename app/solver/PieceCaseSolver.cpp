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
    CaseVariableData *caseVariableData = (CaseVariableData *) dataptr.get();

    if (isValid(*caseVariableData)) {
        resolve(*caseVariableData, depth);
    }
}

void PieceCaseSolver::resolve(CaseVariableData &caseVariableData, int &depth)
{
    // Existance of the data
    unique_ptr<DataInterface> dataptr = move(pathFinder->nextValue(caseVariableData));
    // Casted to use it
    PieceValueData *pieceValueData = (PieceValueData *) dataptr.get();

    // TODO LOGIC
    if (isValid(*pieceValueData)) {
        pieceCaseConstraint->accept(caseVariableData, *pieceValueData, depth);
        ++depth;
        resolve(depth);
        --depth;
        pieceCaseConstraint->rollback(depth);
        pieceCaseConstraint->discard(caseVariableData, *pieceValueData, depth);
    }
}

bool PieceCaseSolver::isValid(CaseVariableData &caseVariableData)
{
    return caseVariableData.isValid();
}

bool PieceCaseSolver::isValid(PieceValueData &pieceValueData)
{
    return pieceValueData.isValid();
}