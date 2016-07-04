#ifndef ETERNITYII_VARIABLEINTERFACE_H
#define ETERNITYII_VARIABLEINTERFACE_H

#include "../../model/ModelInterface.h"

template<class VarD, class ValD>
class VariableInterface
{
protected:
    ModelInterface<VarD, ValD> *modelInterface;
public:
    virtual void initialize(GameImportData &gameData) = 0;

    virtual VarD *next(int &depth) = 0;

    virtual const bool hasNext(int &depth) = 0;

    virtual ~VariableInterface()
    { };
};
#endif //ETERNITYII_VARIABLEINTERFACE_H
