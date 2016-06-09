#ifndef ETERNITYII_SOLVER_H
#define ETERNITYII_SOLVER_H

#include <memory>

#include "PathFinder.h"
#include "DataManager.h"
class Solver
{
public:
    Solver();

    void initialize(PathFinder &pathFinder, DataManager &dataManager);

    /**
     * Begin the resolution process
     */
    void resolve();

private:

    PathFinder *pathFinder;

    DataManager *dataManager;

    /**
     * Recursive resolution method
     */
    void resolve(int &depth);

    void resolve(VariableData &variableData, int &depth);

    bool isValid(ValueData &valueData);

    bool isValid(VariableData &variableData);
    bool isPossible(VariableData &data, ValueData &valueData);
};


#endif //ETERNITYII_SOLVER_H
