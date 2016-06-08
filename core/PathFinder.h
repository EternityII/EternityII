#ifndef ETERNITYII_PATHFINDER_H
#define ETERNITYII_PATHFINDER_H


#include <memory>
#include "pathfinder/VariableInterface.h"
#include "pathfinder/ValueInterface.h"
#include "structures/ValueData.h"
#include "structures/VariableData.h"

using namespace std;

class PathFinder
{
public:
    /**
     * @param valueInterface, value strategy
     * @param variableInterface, variable strategy
     */
    PathFinder();

    void set(unique_ptr<VariableInterface> variableInterface);

    void set(unique_ptr<ValueInterface> valueInterface);

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
    unique_ptr<VariableInterface> variableInterface;
    unique_ptr<ValueInterface> valueInterface;
};


#endif //ETERNITYII_PATHFINDER_H
