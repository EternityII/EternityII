#ifndef ETERNITYII_OBSERVABLEINTERFACE_H
#define ETERNITYII_OBSERVABLEINTERFACE_H

#include <vector>
#include "ObserverInterface.h"

using namespace std;

template<class VarD, class ValD>
class ObservableInterface
{
protected:
    vector<ObserverInterface<VarD, ValD> *> observers;

public:
    void add(ObserverInterface<VarD, ValD> &observer)
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

    //virtual void discard(DataInterface &dataInterface, const int &depth){ };

    virtual ~ObservableInterface()
    { };
};


#endif //ETERNITYII_OBSERVABLEINTERFACE_H
