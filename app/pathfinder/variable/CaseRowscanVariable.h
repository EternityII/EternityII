#ifndef ETERNITYII_CASEROWSCANVARIABLE_H
#define ETERNITYII_CASEROWSCANVARIABLE_H

#include "../../../core/pathfinder/variable/VariableInterface.h"
#include "../../data/variable/CaseData.h"

class CaseRowscanVariable: public VariableInterface
{
    void initialize(GameImportData &gameData)
    {
        //TODO
    }

    CaseData *next(int &depth)
    {
        //TODO
        // For test sake
        CaseData *caseData = new CaseData(true);
        caseData->x = 2;
        caseData->y = 2;
        return caseData;
    }

    const bool hasNext(int &depth)
    {
        //TODO
        return false;
    }
};

#endif //ETERNITYII_CASEROWSCANVARIABLE_H
