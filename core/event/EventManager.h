#ifndef ETERNITYII_EVENT_H
#define ETERNITYII_EVENT_H

#include <memory>
#include <deque>
#include "Element.h"

using namespace std;

class EventManager
{
    deque<unique_ptr<Element>> elements;

public:
    void add(unique_ptr<Element> element)
    {
        elements.emplace_back(move(element));
    }

    void process()
    {
        if (!elements.empty()) {
            elements.front()->execute();
            elements.pop_front();
        }
    }

    const bool empty()
    {
        return elements.empty();
    }

};


#endif //ETERNITYII_EVENT_H
