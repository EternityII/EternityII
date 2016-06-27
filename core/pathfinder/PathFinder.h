#ifndef ETERNITYII_PATHFINDER_H
#define ETERNITYII_PATHFINDER_H

#include <memory>

#include "../data/DataInterface.h"
#include "value/ValueInterface.h"
#include "variable/VariableInterface.h"
#include "../../app/data/variable/CaseData.h"

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
    DataInterface *nextValue(DataInterface &dataInterface);

    /**
     * @param depth the actual depth in the recursion
     *
     * Gets the next Variable depending of the depth
     */
    DataInterface *nextVariable(int &depth);

    const bool hasNextVariable(int &depth);
    const bool hasNextValue(DataInterface &dataInterface);
private:
    unique_ptr<VariableInterface> variableInterface;
    unique_ptr<ValueInterface> valueInterface;
};


#endif //ETERNITYII_PATHFINDER_H
