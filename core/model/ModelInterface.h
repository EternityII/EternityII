#ifndef ETERNITYII_MODELINTERFACE_H
#define ETERNITYII_MODELINTERFACE_H

#include "../../app/io/GameImportData.h"
#include "../ObservableInterface.h"

template<class VarD, class ValD>
class ModelInterface: public ObservableInterface<VarD, ValD>
{
protected:
public:
    virtual void initialize(GameImportData &gameImportData) = 0;

    virtual void accept(VarD &dataInterface, const int &depth) = 0;

    virtual void accept(ValD &dataInterface, const int &depth) = 0;

    virtual void discard(VarD &dataInterface, const int &depth) = 0;

    virtual void discard(ValD &dataInterface, const int &depth) = 0;

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
