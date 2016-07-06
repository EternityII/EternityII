#ifndef ETERNITYII_SOLVERINTERFACE_H
#define ETERNITYII_SOLVERINTERFACE_H

#include "pathfinder/PathFinder.h"
#include "ConstraintInterface.h"
#include "io/data/GameImportData.h"

class SolverInterface
{
public:

    virtual void initialize
        (PathFinder &pathFinder,
            ConstraintInterface &constraintInterface,
            vector<unique_ptr<ModelInterface>> &models,
            GameImportData &gameImportData) =
        0;

    virtual void resolve() = 0;

    virtual ~SolverInterface()
    { };
};


#endif //ETERNITYII_SOLVERINTERFACE_H
