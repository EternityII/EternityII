#ifndef ETERNITYII_COLORDATA_H
#define ETERNITYII_COLORDATA_H

#include "../../../core/data/DataInterface.h"

class ColorData: public DataInterface
{
public:
    int id;

    ColorData()
    {}

    ColorData(const bool &valid)
        : DataInterface(valid)
    {}

    ColorData(const int &id)
        : id(id)
    {};

    ColorData &operator=(const ColorData &colorData)
    {
        id = colorData.id;
        return *this;
    }

    ColorData(const ColorData &colorData)
        : id(colorData.id)
    {};
};


#endif //ETERNITYII_COLORDATA_H
