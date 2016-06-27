#ifndef ETERNITYII_CASEROWSCANVARIABLE_H
#define ETERNITYII_CASEROWSCANVARIABLE_H

#include "../../../core/pathfinder/variable/VariableInterface.h"

class CaseRowscanVariable: public VariableInterface
{
    void initialize(GameImportData &gameData)
    {
        //TODO
    }

    DataInterface *next(int &depth)
    {
        //TODO
        // For test sake
        CaseData *caseData = new CaseData(true);
        caseData->x = 10;
        caseData->y = 50;
        return caseData;
    }

    const bool hasNext(int &depth)
    {
        //TODO
        return false;
    }
};

#endif //ETERNITYII_CASEROWSCANVARIABLE_H
