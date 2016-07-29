#ifndef ETERNITYII_EVENT_H
#define ETERNITYII_EVENT_H

#include <memory>
#include <deque>

using namespace std;

class EventManager
{
    deque<unique_ptr<function<void()>>> elements;

public:
    void add(unique_ptr<function<void()>> element)
    {
        elements.emplace_back(move(element));
    }

    void process()
    {
        if (not elements.empty()) {
            auto ptr = move(elements.front());
            elements.pop_front();
            ptr->operator()();
        }
    }

    const bool empty()
    {
        return elements.empty();
    }

};


#endif //ETERNITYII_EVENT_H
