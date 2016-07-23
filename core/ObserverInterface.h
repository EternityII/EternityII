#ifndef ETERNITYII_OBSERVERINTERFACE_H
#define ETERNITYII_OBSERVERINTERFACE_H

#include "event/EventManager.h"

class ObserverInterface
{
protected:
    EventManager &eventManager;
public:
    ObserverInterface(EventManager &eventManager)
        : eventManager(eventManager)
    { }

    //virtual void allow(DataInterface &varData, DataInterface &valData, const int &depth) = 0;

    //virtual void callback(DataInterface &valData, const int &depth) = 0;

    //virtual void denyOne(DataInterface &varData, DataInterface &valData, const int &depth) = 0;

    //virtual void deny(DataInterface &varData, const int &depth) = 0;
    virtual ~ObserverInterface()
    { }
};

#endif //ETERNITYII_OBSERVERINTERFACE_H
