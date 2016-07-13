#ifndef ETERNITYII_VALUEINTERFACE_H
#define ETERNITYII_VALUEINTERFACE_H

#include "../../model/ModelInterface.h"
#include "../../data/DataInterface.h"


class ValueInterface
{
protected:
    ModelInterface *model;

    ValueInterface()
    { };
public:
    ValueInterface(ModelInterface &model)
    {
        this->model = &model;
    };

    virtual DataInterface *next(DataInterface &data) = 0;

    virtual const bool hasNext(DataInterface &data, const int &depth) = 0;

    virtual ~ValueInterface()
    { };
};

#endif //ETERNITYII_VALUEINTERFACE_H
