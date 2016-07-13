#ifndef ETERNITYII_MODELINTERFACE_H
#define ETERNITYII_MODELINTERFACE_H


#include "../ObservableInterface.h"
#include "../io/data/GameImportData.h"
#include "../event/TypedElement.h"

class ModelInterface: public ObservableInterface
{
protected:
    const int DISCARD = 0;
    const int ACCEPT = 1;

    ModelInterface(EventManager &eventManager)
        : ObservableInterface(eventManager)
    { }
public:
    ModelInterface(GameImportData &gameImport, EventManager &eventManager)
        : ObservableInterface(eventManager)
    { };

    /**
     * Will rollback from "fromDept" to the depth "toDept"
     *
     * !!! Will not rollback depth "toDepth"
     *
     * @param int const &fromDept, the depth to rollback fromDept
     * @param int const &toDepth, the depth to rollback toDepth
     */
    void rollback(const int &fromDept, const int &toDepth)
    {
        for (int depth = fromDept; depth > toDepth; --depth) {
            // they see me rolling ... back
            rollback(depth);
        }
    };

    /**
     * Roll backs the given depth
     *
     * @param int const &depth, the depth to rollback
     */
    virtual void rollback(const int &depth, const bool total = true) = 0;

    virtual ~ModelInterface()
    { };
};


#endif //ETERNITYII_MODELINTERFACE_H
