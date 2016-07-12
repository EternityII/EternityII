#ifndef ETERNITYII_CASEROWSCANVARIABLE_H
#define ETERNITYII_CASEROWSCANVARIABLE_H

#include "../../../core/pathfinder/variable/VariableInterface.h"
#include "../../data/variable/CaseData.h"

class CaseRowscanVariable: public VariableInterface
{
    CaseModel *_modelInterface;
public:
    CaseRowscanVariable(ModelInterface &modelInterface)
    {
        this->_modelInterface = static_cast<CaseModel *>(&modelInterface);
    }

    CaseData *next(int &depth) override
    {
        CaseData *caseData;
        if (depth >= _modelInterface->size * _modelInterface->size) {
            caseData = new CaseData(false);
            return caseData;
        }

        int y = depth / _modelInterface->size;
        int x = depth % _modelInterface->size;
        caseData = new CaseData(y, x);
        if (!_modelInterface->available[y][x]) {
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
