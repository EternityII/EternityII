#ifndef ETERNITYII_VARIABLEINTERFACE_H
#define ETERNITYII_VARIABLEINTERFACE_H

#include "../../../app/io/GameImportData.h"
#include "../../data/DataInterface.h"

class VariableInterface
{
protected:
    ModelInterface *modelInterface;
public:
    virtual void initialize(GameImportData &gameData) = 0;

    virtual DataInterface *next(int &depth) = 0;

    virtual const bool hasNext(int &depth) = 0;
};
#endif //ETERNITYII_VARIABLEINTERFACE_H
