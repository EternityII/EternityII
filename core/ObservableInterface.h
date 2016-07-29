#ifndef ETERNITYII_OBSERVABLEINTERFACE_H
#define ETERNITYII_OBSERVABLEINTERFACE_H

#include <vector>
#include "ObserverInterface.h"
#include "event/EventManager.h"

using namespace std;

class ObservableInterface
{
protected:
    vector<ObserverInterface *> observers;

    EventManager &eventManager;

public:
    ObservableInterface(EventManager &eventManager)
        : eventManager(eventManager)
    {}

    template<class O, typename D>
    void addDenyEvent(O &obj,
        const D &data,
        const int &depth,
        const int &persistent) const
    {
        eventManager.add(make_unique<std::function<void()> >(
            [&obj, data, depth, persistent]
            { obj.deny(data, depth, persistent); }
        ));
    }

    template<class O, typename D1, typename D2>
    void addDenyOneEvent(
        O &obj,
        const D1 &data1,
        const D2 &data2,
        const int &depth,
        const int &persistent) const
    {
        eventManager.add(make_unique<std::function<void()> >(
                [&obj, data1, data2, depth, persistent]
                { obj.denyOne(data1, data2, depth, persistent); }
            ));
    }

    template<class O, typename D1, typename D2>
    void addAddOneEvent(
        O &obj,
        const D1 &data1,
        const D2 &data2) const
    {
        eventManager.add(make_unique<std::function<void()> >(
            [&obj, data1, data2]
            { obj.addOne(data1, data2); }
            ));
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
    //virtual void allow(DataInterface &dataInterface, const int &depth){ };
    //virtual void callback(DataInterface &dataInterface, const int &depth){};

    //virtual void denyOne(DataInterface &dataInterface,DataInterface &dataInterface, const int &depth){ };

    virtual ~ObservableInterface()
    {};
};


#endif //ETERNITYII_OBSERVABLEINTERFACE_H
