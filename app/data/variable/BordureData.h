#ifndef ETERNITYII_BORDUREDATA_H
#define ETERNITYII_BORDUREDATA_H

#include "../../../core/data/DataInterface.h"

class BordureData: public DataInterface
{
public:
    int id;

    BordureData()
    { }

    BordureData(const bool valid)
        : DataInterface(valid)
    { };

    BordureData(const int &id)
        : id(id)
    { };

    BordureData(const BordureData &bordureData)
        : id(bordureData.id)
    { };

};


#endif //ETERNITYII_BORDUREDATA_H
