#ifndef ETERNITYII_PIECEVALUEDATA_H
#define ETERNITYII_PIECEVALUEDATA_H

#include "../../../core/data/DataInterface.h"

class PieceValueData: public DataInterface
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

    PieceValueData()
        : DataInterface()
    { }

    PieceValueData(bool valid)
        : DataInterface(valid)
    { }

    PieceValueData(int id, int rotation)
        : id(id), rotation(rotation)
    { }

};

#endif //ETERNITYII_PIECEVALUEDATA_H
