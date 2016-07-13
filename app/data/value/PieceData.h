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
        : DataInterface()
    { }

    PieceData(bool valid)
        : DataInterface(valid)
    { }

    PieceData(const PieceData &pieceData)
        : DataInterface(pieceData.valid)
    {
        this->id = pieceData.id;
        this->rotation = pieceData.rotation;
    }

    PieceData(const int &id, const int &rotation)
        : id(id), rotation(rotation)
    { }

};

#endif //ETERNITYII_PIECEDATA_H
