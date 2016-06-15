#ifndef ETERNITYII_SOLVERINTERFACE_H
#define ETERNITYII_SOLVERINTERFACE_H

#include "pathfinder/PathFinder.h"
#include "ConstraintInterface.h"

class SolverInterface
{
public:

    virtual void initialize(PathFinder &pathFinder, ConstraintInterface &constraintInterface) = 0;

    virtual void resolve() = 0;
};


#endif //ETERNITYII_SOLVERINTERFACE_H
