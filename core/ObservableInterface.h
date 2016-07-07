#ifndef ETERNITYII_OBSERVABLEINTERFACE_H
#define ETERNITYII_OBSERVABLEINTERFACE_H

#include <vector>
#include "ObserverInterface.h"
#include "event/EventManager.h"
#include "event/TypedElement.h"

using namespace std;

class ObservableInterface
{
protected:
    vector<ObserverInterface *> observers;

    EventManager *eventManager;

public:
    void addEventManager(EventManager &eventManager1)
    {
        this->eventManager = &eventManager1;
    }

    template<typename O, typename D>
    void addAcceptedEvent(O &obj, D &data, const int &depth)
    {
        function<void()> callback =
            bind(static_cast<void (O::*)(D &, const int &)>(&O::accepted), obj, data, depth);
        eventManager->add(make_unique<TypedElement<D>>(callback));
    }

    void add(ObserverInterface &observer)
    {
        observers.push_back(&observer);
    };

    void remove(int &observerIndex)
    {
        observers.erase(observers.begin() + observerIndex);
    };

    /**
     * Informs the all the constraints about the change
     */
    //virtual void accept(DataInterface &dataInterface, const int &depth){ };
    //virtual void callback(DataInterface &dataInterface, const int &depth){};

    //virtual void discard(DataInterface &dataInterface,DataInterface &dataInterface, const int &depth){ };

    virtual ~ObservableInterface()
    { };
};


#endif //ETERNITYII_OBSERVABLEINTERFACE_H
