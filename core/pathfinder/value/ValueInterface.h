#ifndef ETERNITYII_VALUEINTERFACE_H
#define ETERNITYII_VALUEINTERFACE_H

#include "../../../app/io/GameImportData.h"
#include "../../data/DataInterface.h"
#include "../../model/ModelInterface.h"

class ValueInterface
{
protected:
    ModelInterface *modelInterface;
public:
    virtual void initialize(GameImportData &gameImportData) = 0;

    virtual unique_ptr<DataInterface> next(DataInterface &dataInterface) = 0;
};

#endif //ETERNITYII_VALUEINTERFACE_H
