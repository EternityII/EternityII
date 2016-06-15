#ifndef ETERNITYII_MODELINTERFACE_H
#define ETERNITYII_MODELINTERFACE_H

#include "../ObservableInterface.h"
#include "../../app/io/GameImportData.h"

class ModelInterface: public ObservableInterface
{
public:
    virtual void initialize(GameImportData &gameImportData) = 0;

    virtual void rollback(const int &depth) = 0;
};


#endif //ETERNITYII_MODELINTERFACE_H
