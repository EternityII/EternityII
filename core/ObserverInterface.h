#ifndef ETERNITYII_OBSERVERINTERFACE_H
#define ETERNITYII_OBSERVERINTERFACE_H

#include "event/EventManager.h"
class ObserverInterface
{
protected:
    EventManager *eventManager;
public:
    ObserverInterface(EventManager &eventManager)
    {
        this->eventManager = &eventManager;
    }

    //virtual void accept(DataInterface &varData, DataInterface &valData, const int &depth) = 0;

    //virtual void callback(DataInterface &valData, const int &depth) = 0;

    //virtual void discard(DataInterface &varData, DataInterface &valData, const int &depth) = 0;

    //virtual void discarded(DataInterface &varData, const int &depth) = 0;
    virtual ~ObserverInterface()
    { }
};

#endif //ETERNITYII_OBSERVERINTERFACE_H
