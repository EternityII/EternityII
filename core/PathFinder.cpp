#include "PathFinder.h"

PathFinder::PathFinder()
{ }

ValueData PathFinder::nextValue(VariableData &variableData)
{
    return valueInterface->next(variableData);
}

VariableData PathFinder::nextVariable(int &depth)
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