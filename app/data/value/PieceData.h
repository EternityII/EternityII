#ifndef ETERNITYII_PIECEDATA_H
#define ETERNITYII_PIECEDATA_H

#include "../../../core/data/DataInterface.h"

class PieceData: public DataInterface
{
public:
    /**
     * ID de la piece a poser
     */
    int id;
    /**
     * Rotation de la piece
     */
    int rotation;

    PieceData()
    {}

    PieceData(const bool valid)
        : DataInterface(valid)
    {}

    PieceData(const int &id, const int &rotation)
        : id(id), rotation(rotation)
    {}

    PieceData(const PieceData &pieceData)
        : DataInterface(pieceData.valid), id(pieceData.id),
          rotation(pieceData.rotation)
    {}

    /*PieceData &operator=(const PieceData &pieceData)
    {
        id = pieceData.id;
        rotation = pieceData.rotation;

        return *this;
    }*/

    ~PieceData()
    {}

};

#endif //ETERNITYII_PIECEDATA_H
