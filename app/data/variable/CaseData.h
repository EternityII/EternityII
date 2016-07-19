#ifndef ETERNITYII_CASEDATA_H
#define ETERNITYII_CASEDATA_H

#include "../../../core/data/DataInterface.h"

class CaseData: public DataInterface
{
public:
    int x;
    int y;

    CaseData()
    { }

    CaseData(const bool valid)
        : DataInterface(valid)
    { };

    CaseData(const int &x, const int &y)
        : x(x), y(y)
    { }

    CaseData(const CaseData &caseData)
        : DataInterface(caseData.valid), x(caseData.x), y(caseData.y)
    { };
};

#endif //ETERNITYII_CASEDATA_H
