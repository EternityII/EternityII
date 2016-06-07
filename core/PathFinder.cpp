#include "PathFinder.h"

PathFinder::PathFinder(ValueInterface &valueInterface, VariableInterface &variableInterface)
    : valueInterface(valueInterface), variableInterface(variableInterface)
{ }

ValueData PathFinder::nextValue(VariableData &variableData)
{
    return valueInterface.next(variableData);
}

VariableData PathFinder::nextVariable(int &depth)
{
    return variableInterface.next(depth);
}
