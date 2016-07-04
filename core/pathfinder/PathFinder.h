#ifndef ETERNITYII_PATHFINDER_H
#define ETERNITYII_PATHFINDER_H

#include <memory>
#include "variable/VariableInterface.h"
#include "value/ValueInterface.h"

using namespace std;

template<class VarD, class ValD>
class PathFinder
{
public:
    /**
     * @param valueInterface, value strategy
     * @param variableInterface, variable strategy
     */
    PathFinder()
    { };

    void set(unique_ptr<VariableInterface<VarD, ValD>> variableInterface)
    {
        this->variableInterface = move(variableInterface);
    }

    void set(unique_ptr<ValueInterface<VarD, ValD>> valueInterface)
    {
        this->valueInterface = move(valueInterface);
    }

    /**
     * @param variableData the variable to look at
     *
     * Gets the next Value depending of the variableData
     */
    ValD *nextValue(VarD &variableData)
    {
        return valueInterface->next(variableData);
    }

    /**
     * @param depth the actual depth in the recursion
     *
     * Gets the next VarM depending of the depth
     */
    VarD *nextVariable(int &depth)
    {
        return variableInterface->next(depth);
    };

    const bool hasNextVariable(int &depth)
    {
        return variableInterface->hasNext(depth);
    }

    const bool hasNextValue(VarD &variableData)
    {
        return valueInterface->hasNext(variableData);
    }
private:
    unique_ptr<VariableInterface<VarD, ValD>> variableInterface;
    unique_ptr<ValueInterface<VarD, ValD>> valueInterface;
};


#endif //ETERNITYII_PATHFINDER_H
