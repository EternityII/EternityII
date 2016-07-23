#ifndef ETERNITYII_DATAINTERFACE_H
#define ETERNITYII_DATAINTERFACE_H

class DataInterface
{
public:
    bool valid;

    DataInterface()
        : valid(true)
    {}

    DataInterface(const bool &valid)
        : valid(valid)
    {}

    virtual ~DataInterface()
    {}
};

#endif //ETERNITYII_DATAINTERFACE_H
