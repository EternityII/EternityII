#ifndef ETERNITYII_CASEROWSCANVARIABLE_H
#define ETERNITYII_CASEROWSCANVARIABLE_H

#include "../../../core/pathfinder/variable/VariableInterface.h"
#include "../../model/CaseModel.h"

class CaseRowscanVariable: public VariableInterface
{
    CaseModel *_model;

    vector<vector<int>> coordinates;

public:
    CaseRowscanVariable(CaseModel &model)
    {
        this->_model = &model;

        // mapping the coordinates
        coordinates.resize(_model->size * _model->size, vector<int>(2, 0));
        for (int x = 0; x < _model->size; ++x) {
            for (int y = 0; y < _model->size; ++y) {
                int depth = x * _model->size + y;
                coordinates[depth][0] = x;
                coordinates[depth][1] = y;
            }
        }
    }

    CaseData *next(int &depth) override
    {
        CaseData *caseData;

        if (depth >= _model->size * _model->size) {
            return new CaseData(false);
        }

        int &coord_x = coordinates[depth][0];
        int &coord_y = coordinates[depth][1];
        caseData = new CaseData(coord_x, coord_y);
        if (!_model->available[coord_x][coord_y]) {
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
