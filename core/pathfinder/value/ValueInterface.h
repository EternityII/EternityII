#ifndef ETERNITYII_VALUEINTERFACE_H
#define ETERNITYII_VALUEINTERFACE_H

#include "../../model/ModelInterface.h"

template<class VarD, class ValD>
class ValueInterface
{
protected:
    ModelInterface<VarD, ValD> *modelInterface;
public:
    virtual void initialize(GameImportData &gameImportData) = 0;

    virtual ValD *next(VarD &dataInterface) = 0;

    virtual const bool hasNext(VarD &dataInterface) = 0;

    virtual ~ValueInterface()
    { };
};

#endif //ETERNITYII_VALUEINTERFACE_H
