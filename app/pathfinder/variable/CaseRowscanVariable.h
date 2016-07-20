#ifndef ETERNITYII_CASEROWSCANVARIABLE_H
#define ETERNITYII_CASEROWSCANVARIABLE_H

#include "../../../core/pathfinder/variable/VariableInterface.h"
#include "../../model/CaseModel.h"

class CaseRowscanVariable: public VariableInterface
{
    CaseModel &_model;

    vector<vector<int>> coordinates;

public:
    CaseRowscanVariable(CaseModel &model)
        : _model(model)
    {
        // mapping the coordinates
        coordinates.resize(_model.size * _model.size, vector<int>(2, 0));
        for (int x = 0; x < _model.size; ++x) {
            for (int y = 0; y < _model.size; ++y) {
                int depth = x * _model.size + y;
                coordinates[depth][0] = x;
                coordinates[depth][1] = y;
            }
        }
    }

    CaseData *next(int &depth) override
    {
        return new CaseData(coordinates[depth][0], coordinates[depth][1]);;
    }

    const bool hasNext(int &depth) override
    {
        return depth < _model.nbCases &&
            _model.available[coordinates[depth][0]][coordinates[depth][1]];
    }
};

#endif //ETERNITYII_CASEROWSCANVARIABLE_H
