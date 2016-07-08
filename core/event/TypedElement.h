//
// Created by stardisblue on 07/07/16.
//

#ifndef ETERNITYII_TYPEDELEMENTS_H
#define ETERNITYII_TYPEDELEMENTS_H

#include <functional>
#include "Element.h"

using namespace std;

template<class Data>
class TypedElement: public Element
{
    unique_ptr<std::function<void()>> funct;
    Data *data;
    int depth;

public:
    TypedElement(unique_ptr<std::function<void()>> callback)
    {
        this->funct = move(callback);
    }

    ~TypedElement()
    {

    }

    void execute()
    {
        this->funct->operator()();
    }

};


#endif //ETERNITYII_TYPEDELEMENTS_H
