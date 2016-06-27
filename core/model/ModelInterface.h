#ifndef ETERNITYII_MODELINTERFACE_H
#define ETERNITYII_MODELINTERFACE_H

#include "../ObservableInterface.h"
#include "../../app/io/GameImportData.h"

class ModelInterface: public ObservableInterface
{
protected:
    int actualDepth;
public:
    virtual void initialize(GameImportData &gameImportData) = 0;

    /**
     * @param int const &depth, the depth
     *
     * Rolls back the model to depth
     */
    virtual void rollback(const int &depth) = 0;

    virtual ~ModelInterface()
    { };
};


#endif //ETERNITYII_MODELINTERFACE_H
