#ifndef ETERNITYII_SOLVERINTERFACE_H
#define ETERNITYII_SOLVERINTERFACE_H

#include "pathfinder/PathFinder.h"
#include "ConstraintInterface.h"
#include "io/data/GameImportData.h"

class SolverInterface
{
protected:
    PathFinder &pathFinder;

    vector<unique_ptr<ModelInterface>> &models;

    GameImportData &game;

    ConstraintInterface *constraint;

    SolverInterface(PathFinder &pathFinder,
        vector<unique_ptr<ModelInterface>> &models,
        GameImportData &gameImport)
        : pathFinder(pathFinder), models(models), game(gameImport)
    { }

public:
    SolverInterface
        (PathFinder &pathFinder,
            vector<unique_ptr<ModelInterface>> &models,
            GameImportData &gameImport,
            ConstraintInterface &constraint)
        : pathFinder(pathFinder), models(models), game(gameImport)
    {
        this->constraint = &constraint;
    };

    virtual void resolve() = 0;

    virtual ~SolverInterface()
    { };
};


#endif //ETERNITYII_SOLVERINTERFACE_H
