//
// Created by stardisblue on 07/07/16.
//

#ifndef ETERNITYII_EVENT_H
#define ETERNITYII_EVENT_H

#include <memory>
#include <queue>
#include "Element.h"

using namespace std;

class EventManager
{
    queue<unique_ptr<Element>> elements;

public:
    void add(unique_ptr<Element> element)
    {
        elements.push(move(element));
    }

    void pop()
    {
        if (!elements.empty()) {
            elements.front()->execute();
            elements.pop();
        }
    }

    const bool empty()
    {
        return elements.empty();
    }

};


#endif //ETERNITYII_EVENT_H
