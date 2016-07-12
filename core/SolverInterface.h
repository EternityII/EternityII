#ifndef ETERNITYII_SOLVERINTERFACE_H
#define ETERNITYII_SOLVERINTERFACE_H

#include "pathfinder/PathFinder.h"
#include "ConstraintInterface.h"
#include "io/data/GameImportData.h"

class SolverInterface
{
protected:
    PathFinder *pathFinder;

    vector<unique_ptr<ModelInterface>> *models;

    GameImportData *game;

    ConstraintInterface *constraintInterface;

    SolverInterface(PathFinder &pathFinder, vector<unique_ptr<ModelInterface>> &models, GameImportData &gameImportData)
    {
        this->pathFinder = &pathFinder;
        this->models = &models;
        this->game = &gameImportData;
    }

public:
    SolverInterface
        (PathFinder &pathFinder,
            ConstraintInterface &constraintInterface,
            vector<unique_ptr<ModelInterface>> &models,
            GameImportData &gameImportData)
    {
        this->pathFinder = &pathFinder;
        this->models = &models;
        this->game = &gameImportData;
        this->constraintInterface = &constraintInterface;
    };

    virtual void resolve() = 0;

    virtual ~SolverInterface()
    { };
};


#endif //ETERNITYII_SOLVERINTERFACE_H
