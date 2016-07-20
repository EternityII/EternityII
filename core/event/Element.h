#ifndef ETERNITYII_ELEMENT_H
#define ETERNITYII_ELEMENT_H

#include <functional>
#include <memory>
#include "Element.h"

class Element
{
    std::unique_ptr<std::function<void()>> funct;

public:
    Element(std::unique_ptr<std::function<void()>> callback)
    {
        this->funct = move(callback);
    }

    ~Element()
    {

    }

    void execute()
    {
        this->funct->operator()();
    }
};

#endif //ETERNITYII_ELEMENT_H
