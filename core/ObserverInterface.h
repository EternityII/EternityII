#ifndef ETERNITYII_OBSERVERINTERFACE_H
#define ETERNITYII_OBSERVERINTERFACE_H

class ObserverInterface
{
public:
    //virtual void accept(DataInterface &varData, DataInterface &valData, const int &depth) = 0;

    //virtual void accepted(DataInterface &valData, const int &depth) = 0;

    //virtual void discard(DataInterface &varData, DataInterface &valData, const int &depth) = 0;

    //virtual void discarded(DataInterface &varData, const int &depth) = 0;
    virtual ~ObserverInterface()
    { }
};

#endif //ETERNITYII_OBSERVERINTERFACE_H
