#ifndef ETERNITYII_PATHFINDER_H
#define ETERNITYII_PATHFINDER_H

#include <memory>
#include "variable/VariableInterface.h"
#include "value/ValueInterface.h"
#include "../../app/data/variable/CaseData.h"

using namespace std;

class PathFinder
{
public:
    /**
     * @param value, value strategy
     * @param variable, variable strategy
     */
    PathFinder(unique_ptr<VariableInterface> variable,
        unique_ptr<ValueInterface> value)
    {
        this->variable = move(variable);
        this->value = move(value);
    };

    /**
     * @param variableData the variable to look at
     *
     * Gets the next Value depending of the variableData
     */
    DataInterface *nextValue(DataInterface &variable)
    {
        return value->next(variable);
    }

    /**
     * @param depth the actual depth in the recursion
     *
     * Gets the next VarM depending of the depth
     */
    DataInterface *nextVariable(int &depth)
    {
        return variable->next(depth);
    };

    const bool hasNextVariable(int &depth)
    {
        return variable->hasNext(depth);
    }

    const bool hasNextValue(DataInterface &variable, const int &depth)
    {
        return value->hasNext(variable, depth);
    }

private:
    unique_ptr<VariableInterface> variable;
    unique_ptr<ValueInterface> value;
};


#endif //ETERNITYII_PATHFINDER_H
