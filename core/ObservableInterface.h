#ifndef ETERNITYII_OBSERVABLEINTERFACE_H
#define ETERNITYII_OBSERVABLEINTERFACE_H

#include <vector>

#include "ObserverInterface.h"
#include "../app/data/variable/CaseData.h"

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

    virtual void accept(DataInterface &dataInterface, const int &depth) = 0;

    virtual void discard(DataInterface &dataInterface, const int &depth) = 0;

    virtual ~ObservableInterface()
    { };
};


#endif //ETERNITYII_OBSERVABLEINTERFACE_H
