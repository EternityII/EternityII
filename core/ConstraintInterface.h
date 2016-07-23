#ifndef ETERNITYII_CONSTRAINTINTERFACE_H
#define ETERNITYII_CONSTRAINTINTERFACE_H

#include "ObserverInterface.h"
#include "model/ModelInterface.h"

class ConstraintInterface: public ObserverInterface
{
public:

    ConstraintInterface(ModelInterface &first,
        ModelInterface &second,
        EventManager &eventManager)
        : ObserverInterface(eventManager), first(&first), second(&second)
    {
        this->first->add(*this);
        this->second->add(*this);

    }

    virtual ~ConstraintInterface()
    { };

protected:
    ModelInterface *first;
    ModelInterface *second;

    ConstraintInterface(EventManager &eventManager)
        : ObserverInterface(eventManager)
    { };

};

#endif //ETERNITYII_CONSTRAINTINTERFACE_H
