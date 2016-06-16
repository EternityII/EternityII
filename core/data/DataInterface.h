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
};

#endif //ETERNITYII_DATAINTERFACE_H
