#ifndef ETERNITYII_ITERATORMANAGER_H
#define ETERNITYII_ITERATORMANAGER_H

#include <vector>
#include <bits/unique_ptr.h>

#include "structures/ValueData.h"
#include "structures/VariableData.h"
#include "pathfinder/ValueInterface.h"
#include "pathfinder/VariableInterface.h"

using namespace std;

class PathFinder
{
public:
    /**
     * @param valueInterface, value strategy
     * @param variableInterface, variable strategy
     */
    PathFinder(ValueInterface &valueInterface, VariableInterface &variableInterface);

    /**
     * @param variableData the variable to look at
     *
     * Gets the next Value depending of the variableData
     */
    ValueData nextValue(VariableData &variableData);

    /**
     * @param depth the actual depth in the recursion
     *
     * Gets the next Variable depending of the depth
     */
    VariableData nextVariable(int &depth);

private:
    VariableInterface &variableInterface;
    ValueInterface &valueInterface;
};


#endif //ETERNITYII_ITERATORMANAGER_H
