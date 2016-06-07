//
// Created by stardisblue on 06/06/16.
//

#ifndef ETERNITYII_RESOLUTION_H
#define ETERNITYII_RESOLUTION_H


#include "PathFinder.h"
#include "DataManager.h"
#include "structures/ValueData.h"
#include "structures/VariableData.h"
class Solver
{
public:
    Solver(PathFinder &pathFinder1, DataManager &dataManager1);

    /**
     * Begin the resolution process
     */
    void resolve();

private:

    PathFinder &pathFinder;

    DataManager &dataManager;

    /**
     * Recursive resolution method
     */
    void resolve(int &depth);

    void resolve(VariableData &variableData, int &depth);

    bool isValid(ValueData &valueData);

    bool isValid(VariableData &variableData);

    bool isPossible(VariableData &data, ValueData &valueData);
};


#endif //ETERNITYII_RESOLUTION_H
