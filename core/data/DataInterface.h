#ifndef ETERNITYII_DATAINTERFACE_H
#define ETERNITYII_DATAINTERFACE_H

#include <iostream>

using namespace std;

class DataInterface
{
public:
    bool valid;

    DataInterface()
        : valid(true)
    { }

    DataInterface(bool valid)
        : valid(valid)
    { }

    virtual ~DataInterface()
    { }
};

#endif //ETERNITYII_DATAINTERFACE_H
