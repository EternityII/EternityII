#include "PathFinder.h"

PathFinder::PathFinder()
{ }

const bool PathFinder::hasNextValue(DataInterface &dataInterface)
{
    return valueInterface->hasNext(dataInterface);
}

DataInterface *PathFinder::nextValue(DataInterface &dataInterface)
{
    return valueInterface->next(dataInterface);
}

const bool PathFinder::hasNextVariable(int &depth)
{
    return variableInterface->hasNext(depth);
}
DataInterface *PathFinder::nextVariable(int &depth)
{
    return variableInterface->next(depth);
}

void PathFinder::set(unique_ptr<VariableInterface> variableInterface)
{
    this->variableInterface = move(variableInterface);
}

void PathFinder::set(unique_ptr<ValueInterface> valueInterface)
{
    this->valueInterface = move(valueInterface);
}
