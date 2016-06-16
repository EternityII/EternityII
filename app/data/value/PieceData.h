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

    PieceData(int id, int rotation)
        : id(id), rotation(rotation)
    { }

};

#endif //ETERNITYII_PIECEDATA_H
