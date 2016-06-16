#ifndef ETERNITYII_CASEROWSCANVARIABLE_H
#define ETERNITYII_CASEROWSCANVARIABLE_H

#include "../../../core/pathfinder/variable/VariableInterface.h"

class CaseRowscanVariable: public VariableInterface
{
    void initialize(GameImportData &gameData)
    {
        //TODO
    }

    unique_ptr<DataInterface> next(int &depth)
    {
        //TODO
        // For test sake
        unique_ptr<CaseData> caseData = make_unique<CaseData>(true);
        caseData->x = 10;
        caseData->y = 50;
        return move(caseData);
    }
};

#endif //ETERNITYII_CASEROWSCANVARIABLE_H
