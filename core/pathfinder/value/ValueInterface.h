#ifndef ETERNITYII_VALUEINTERFACE_H
#define ETERNITYII_VALUEINTERFACE_H

#include "../../model/ModelInterface.h"

class ValueInterface
{
protected:
    ModelInterface *modelInterface;
public:
    virtual void initialize(ModelInterface &modelInterface)
    {
        this->modelInterface = &modelInterface;
    };

    virtual DataInterface *next(DataInterface &dataInterface) = 0;

    virtual const bool hasNext(DataInterface &dataInterface, const int &depth) = 0;

    virtual ~ValueInterface()
    { };
};

#endif //ETERNITYII_VALUEINTERFACE_H
