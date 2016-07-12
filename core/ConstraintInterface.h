#ifndef ETERNITYII_CONSTRAINTINTERFACE_H
#define ETERNITYII_CONSTRAINTINTERFACE_H

#include "ObserverInterface.h"
#include "model/ModelInterface.h"

class ConstraintInterface: public ObserverInterface
{
public:

    ConstraintInterface(ModelInterface &firstModel, ModelInterface &secondModel, EventManager &eventManager)
        : ObserverInterface(eventManager)
    {
        this->first = &firstModel;
        this->second = &secondModel;
        first->add(*this);
        second->add(*this);

    }

    /**
     * When the iteration is rolledback to depth
     */
    virtual void rollback(const int &from, const int &to) = 0;

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
