#ifndef ETERNITYII_VALUEDATA_H
#define ETERNITYII_VALUEDATA_H


#include "ValidData.h"
/**
 * Informations sur la piece a poser
 */

struct ValueData: public ValidData
{
    /**
     * ID de la piece a poser
     */
    int id;
    /**
     * Rotation de la piece
     */
    int rotation;

};

#endif //ETERNITYII_VALUEDATA_H
