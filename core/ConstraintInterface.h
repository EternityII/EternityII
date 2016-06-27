#ifndef ETERNITYII_CONSTRAINTINTERFACE_H
#define ETERNITYII_CONSTRAINTINTERFACE_H

#include "ObserverInterface.h"
#include "model/ModelInterface.h"

class ConstraintInterface: public ObserverInterface
{
public:

    /**
     * When the iteration is rolledback to depth
     */
    virtual void rollback(const int &depth) = 0;

    virtual void setFirst(ModelInterface &modelInterface)
    {
        this->first = &modelInterface;

        first->add(*this);
    }

    virtual void setSecond(ModelInterface &modelInterface)
    {
        this->second = &modelInterface;

        second->add(*this);
    }

    virtual ~ConstraintInterface()
    { };
protected:
    ModelInterface *first;
    ModelInterface *second;
};

#endif //ETERNITYII_CONSTRAINTINTERFACE_H
