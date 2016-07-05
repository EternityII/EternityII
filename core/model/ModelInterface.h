#ifndef ETERNITYII_MODELINTERFACE_H
#define ETERNITYII_MODELINTERFACE_H

#include "../../app/io/GameImportData.h"
#include "../ObservableInterface.h"
#include "../data/DataInterface.h"

class ModelInterface: public ObservableInterface
{
protected:
public:
    virtual void initialize(GameImportData &gameImportData) = 0;

    /**
     * @param int const &depth, the depth
     *
     * Rolls back the model to depth
     */
    virtual void rollback(const int &from, const int &to) = 0;

    virtual ~ModelInterface()
    { };
};


#endif //ETERNITYII_MODELINTERFACE_H
