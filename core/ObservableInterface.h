#ifndef ETERNITYII_OBSERVABLEINTERFACE_H
#define ETERNITYII_OBSERVABLEINTERFACE_H

#include <vector>

#include "ObserverInterface.h"

using namespace std;

class ObservableInterface
{
    vector<ObserverInterface *> observers;

public:
    void add(ObserverInterface &observer)
    {
        observers.push_back(&observer);
    };

    void remove(int &observerIndex)
    {
        observers.erase(observers.begin() + observerIndex);
    };

    virtual void accept(DataInterface &dataInterface) = 0;

    virtual void discard(DataInterface &dataInterface) = 0;
};


#endif //ETERNITYII_OBSERVABLEINTERFACE_H
