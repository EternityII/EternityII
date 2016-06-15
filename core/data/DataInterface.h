#ifndef ETERNITYII_DATAINTERFACE_H
#define ETERNITYII_DATAINTERFACE_H

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

    bool isValid()
    {
        return this->valid;
    }
};

#endif //ETERNITYII_DATAINTERFACE_H
