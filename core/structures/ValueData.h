//
// Created by stardisblue on 07/06/16.
//

#ifndef ETERNITYII_VALUESTRUCT_H
#define ETERNITYII_VALUESTRUCT_H

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

#endif //ETERNITYII_VALUESTRUCT_H
