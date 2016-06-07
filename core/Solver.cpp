//
// Created by stardisblue on 06/06/16.
//

#include "Solver.h"

Solver::Solver(PathFinder &pathFinder1, DataManager &dataManager1)
    : dataManager(dataManager1), pathFinder(pathFinder1)
{ }

void Solver::resolve()
{
    int depth = 0;

    resolve(depth);
}

void Solver::resolve(int &depth)
{
    VariableData variableData = pathFinder.nextVariable(depth);

    if (isValid(variableData)) {
        resolve(variableData, depth);
    }
}

void Solver::resolve(VariableData &variableData, int &depth)
{
    ValueData valueData = pathFinder.nextValue(variableData);

    if (isValid(valueData)) {
        if (isPossible(variableData, valueData)) {
            dataManager.accept(variableData, valueData);
            resolve(++depth);
            dataManager.rollback(depth);
            dataManager.discard(variableData, valueData);
        }
        resolve(variableData, depth);
    }
}

bool Solver::isValid(VariableData &variableData)
{
    return variableData.valid;
}

bool Solver::isValid(ValueData &valueData)
{
    return valueData.valid;
}

bool Solver::isPossible(VariableData &data, ValueData &valueData)
{
    //TODO :
}
