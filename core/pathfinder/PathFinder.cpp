#include "PathFinder.h"

PathFinder::PathFinder()
{ }

unique_ptr<DataInterface>  PathFinder::nextValue(DataInterface &dataInterface)
{
    return valueInterface->next(dataInterface);
}

unique_ptr<DataInterface>  PathFinder::nextVariable(int &depth)
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