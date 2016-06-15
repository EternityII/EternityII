#ifndef ETERNITYII_CASEVARIABLEDATA_H
#define ETERNITYII_CASEVARIABLEDATA_H

#include "../../../core/data/DataInterface.h"

class CaseVariableData: public DataInterface
{
public:
    int x;
    int y;

    CaseVariableData()
        : DataInterface()
    { }

    CaseVariableData(bool valid)
        : DataInterface(valid)
    { };

    CaseVariableData(int &x, int &y)
        : DataInterface(true), x(x), y(y)
    { }
};

#endif //ETERNITYII_CASEVARIABLEDATA_H
