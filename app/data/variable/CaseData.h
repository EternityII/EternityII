#ifndef ETERNITYII_CASEDATA_H
#define ETERNITYII_CASEDATA_H

#include "../../../core/data/DataInterface.h"

class CaseData: public DataInterface
{
public:
    int x;
    int y;

    CaseData()
        : DataInterface()
    { }

    CaseData(bool valid)
        : DataInterface(valid)
    { };

    CaseData(int &x, int &y)
        : DataInterface(true), x(x), y(y)
    { }
};

#endif //ETERNITYII_CASEDATA_H
