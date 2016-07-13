#ifndef ETERNITYII_VARIABLEINTERFACE_H
#define ETERNITYII_VARIABLEINTERFACE_H

#include "../../model/ModelInterface.h"
#include "../../data/DataInterface.h"

class VariableInterface
{
protected:
    ModelInterface *modelInterface;

    VariableInterface()
    { }

public:
    VariableInterface(ModelInterface &modelInterface)
    {
        this->modelInterface = &modelInterface;
    };

    virtual DataInterface *next(int &depth) = 0;

    virtual const bool hasNext(int &depth) = 0;

    virtual ~VariableInterface()
    { };
};
#endif //ETERNITYII_VARIABLEINTERFACE_H
