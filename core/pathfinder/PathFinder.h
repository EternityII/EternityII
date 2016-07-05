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
     * @param valueInterface, value strategy
     * @param variableInterface, variable strategy
     */
    PathFinder()
    { };

    void set(unique_ptr<VariableInterface> variableInterface)
    {
        this->variableInterface = move(variableInterface);
    }

    void set(unique_ptr<ValueInterface> valueInterface)
    {
        this->valueInterface = move(valueInterface);
    }

    /**
     * @param variableData the variable to look at
     *
     * Gets the next Value depending of the variableData
     */
    DataInterface *nextValue(DataInterface &variableData)
    {
        return valueInterface->next(variableData);
    }

    /**
     * @param depth the actual depth in the recursion
     *
     * Gets the next VarM depending of the depth
     */
    DataInterface *nextVariable(int &depth)
    {
        return variableInterface->next(depth);
    };

    const bool hasNextVariable(int &depth)
    {
        return variableInterface->hasNext(depth);
    }

    const bool hasNextValue(DataInterface &variableData)
    {
        return valueInterface->hasNext(variableData);
    }
private:
    unique_ptr<VariableInterface> variableInterface;
    unique_ptr<ValueInterface> valueInterface;
};


#endif //ETERNITYII_PATHFINDER_H
