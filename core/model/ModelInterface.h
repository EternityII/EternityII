#ifndef ETERNITYII_MODELINTERFACE_H
#define ETERNITYII_MODELINTERFACE_H

#include "../ObservableInterface.h"
#include "../data/DataInterface.h"
#include "../io/data/GameImportData.h"

class ModelInterface: public ObservableInterface
{
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
