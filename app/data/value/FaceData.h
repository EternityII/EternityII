#ifndef ETERNITYII_FACEDATA_H
#define ETERNITYII_FACEDATA_H

#include "../../../core/data/DataInterface.h"

class FaceData: public DataInterface
{
public:
    int id;

    FaceData()
    { }

    FaceData(const bool valid)
        : DataInterface(valid)
    { }

    FaceData(const int &id)
        : id(id)
    { };

    FaceData(const FaceData &faceData)
        : id(faceData.id)
    { };
};


#endif //ETERNITYII_FACEDATA_H
