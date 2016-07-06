#ifndef ETERNITYII_VARIABLEINTERFACE_H
#define ETERNITYII_VARIABLEINTERFACE_H

#include "../../model/ModelInterface.h"
#include "../../data/DataInterface.h"

class VariableInterface
{
protected:
    ModelInterface *modelInterface;
public:
    virtual void initialize(ModelInterface &modelInterface)
    {
        this->modelInterface = &modelInterface;
    };

    virtual DataInterface *next(int &depth) = 0;

    virtual const bool hasNext(int &depth) = 0;

    virtual ~VariableInterface()
    { };
};
#endif //ETERNITYII_VARIABLEINTERFACE_H
