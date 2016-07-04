#ifndef ETERNITYII_CONSTRAINTINTERFACE_H
#define ETERNITYII_CONSTRAINTINTERFACE_H

#include "ObserverInterface.h"

template<class VarM, class ValM, class VarD, class ValD>
class ConstraintInterface: public ObserverInterface<VarD, ValD>
{
public:

    /**
     * When the iteration is rolledback to depth
     */
    virtual void rollback(const int &depth) = 0;

    virtual void setFirst(VarM &modelInterface)
    {
        this->first = &modelInterface;

        first->add(*this);
    }

    virtual void setSecond(ValM &modelInterface)
    {
        this->second = &modelInterface;

        second->add(*this);
    }

    virtual ~ConstraintInterface()
    { };
protected:
    VarM *first;
    ValM *second;
};

#endif //ETERNITYII_CONSTRAINTINTERFACE_H
