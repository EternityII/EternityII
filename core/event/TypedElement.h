//
// Created by stardisblue on 07/07/16.
//

#ifndef ETERNITYII_TYPEDELEMENTS_H
#define ETERNITYII_TYPEDELEMENTS_H

#include <functional>
#include "Element.h"

template<class Data>
class TypedElement: public Element
{
    std::function<void()> function;
    Data *data;
    int depth;

public:
    TypedElement(std::function<void()> &callback)
    {
        this->function = callback;
    }

    ~TypedElement()
    {

    }

    void execute()
    {
        this->function();
    }

};


#endif //ETERNITYII_TYPEDELEMENTS_H
