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

    CaseData(const int &x, const int &y)
        : DataInterface(true), x(x), y(y)
    { }

    CaseData(const CaseData &caseData)
        : DataInterface(caseData.valid)
    {
        this->x = caseData.x;
        this->y = caseData.y;
    };
};

#endif //ETERNITYII_CASEDATA_H
