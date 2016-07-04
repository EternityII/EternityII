#ifndef ETERNITYII_SOLVERINTERFACE_H
#define ETERNITYII_SOLVERINTERFACE_H

#include "pathfinder/PathFinder.h"
#include "ConstraintInterface.h"

template<class VarM, class ValM, class VarD, class ValD>
class SolverInterface
{
public:

    virtual void initialize
        (PathFinder<VarD, ValD> &pathFinder, ConstraintInterface<VarM, ValM, VarD, ValD> &constraintInterface) = 0;

    virtual void resolve() = 0;

    virtual ~SolverInterface()
    { };
};


#endif //ETERNITYII_SOLVERINTERFACE_H
