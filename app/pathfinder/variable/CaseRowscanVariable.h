#ifndef ETERNITYII_CASEROWSCANVARIABLE_H
#define ETERNITYII_CASEROWSCANVARIABLE_H

#include "../../../core/pathfinder/variable/VariableInterface.h"
#include "../../data/variable/CaseData.h"

class CaseRowscanVariable: public VariableInterface
{
    CaseModel *_modelInterface;
public:
    void initialize(ModelInterface &modelInterface) override
    {
        this->_modelInterface = static_cast<CaseModel *>(&modelInterface);
    }

    CaseData *next(int &depth) override
    {
        CaseData *caseData;

        int y = depth / _modelInterface->size;
        int x = depth % _modelInterface->size;
        caseData = new CaseData(x, y);
        if (!_modelInterface->isAvailable[x][y]) {
            caseData->valid = false;
        }

        return caseData;
    }

    const bool hasNext(int &depth) override
    {
        //because if has not next then it's impossible
        return false;
    }
};

#endif //ETERNITYII_CASEROWSCANVARIABLE_H
