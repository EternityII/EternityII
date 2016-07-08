#ifndef ETERNITYII_MODELINTERFACE_H
#define ETERNITYII_MODELINTERFACE_H


#include "../ObservableInterface.h"
#include "../io/data/GameImportData.h"
#include "../event/TypedElement.h"

class ModelInterface: public ObservableInterface
{
public:
    virtual void initialize(GameImportData &gameImportData) = 0;

    /**
     * @param int const &depth, the depth
     *
     * Rolls back the model to depth
     */
    void rollback(const int &from, const int &to)
    {
        for (int depth = from; depth > to; --depth) {
            // they see me rolling ... back
            rollback(depth);
        }
    };

    virtual void rollback(const int &depth) = 0;

    virtual ~ModelInterface()
    { };
};


#endif //ETERNITYII_MODELINTERFACE_H
