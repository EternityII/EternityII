//
// Created by stardisblue on 07/06/16.
//

#ifndef ETERNITYII_VARSTRUCT_H
#define ETERNITYII_VARSTRUCT_H

#include "ValidData.h"
/**
 * Coordonnées de la case
 */
struct VariableData: public ValidData
{
    int x;
    int y;

    VariableData()
    { }

    VariableData(bool valid)
    {
        this->valid = valid;
    }

    VariableData(int &x, int &y)
    {
        this->x = x;
        this->y = y;
    }
};

#endif //ETERNITYII_VARSTRUCT_H
