#ifndef ETERNITYII_OBSERVABLEINTERFACE_H
#define ETERNITYII_OBSERVABLEINTERFACE_H

#include <vector>
#include "ObserverInterface.h"

using namespace std;

class ObservableInterface
{
protected:
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

    /**
     * Informs the all the constraints about the change
     */
    //virtual void accept(DataInterface &dataInterface, const int &depth){ };
    //virtual void accepted(DataInterface &dataInterface, const int &depth){};

    //virtual void discard(DataInterface &dataInterface,DataInterface &dataInterface, const int &depth){ };

    virtual ~ObservableInterface()
    { };
};


#endif //ETERNITYII_OBSERVABLEINTERFACE_H
