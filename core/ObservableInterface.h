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
    ObservableInterface(EventManager &eventManager)
    {
        this->eventManager = &eventManager;
    }

    template<typename O, typename D>
    void addAcceptedEvent(O &obj, D &data, const int &depth)
    {
        unique_ptr<std::function<void()>> callback =
            make_unique<std::function<void()>>(
                bind(static_cast<void (O::*)(D &, const int &)>(&O::accepted), obj, data, depth));
        eventManager->add(make_unique<TypedElement<D>>(move(callback)));
    }

    template<typename O, typename D>
    void addDiscardedEvent(O &obj, D &data, const int &depth)
    {
        unique_ptr<std::function<void()>> callback =
            make_unique<std::function<void()>>(
                bind(static_cast<void (O::*)(D &, const int &)>(&O::discarded), obj, data, depth));
        eventManager->add(make_unique<TypedElement<D>>(move(callback)));
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
