#ifndef ETERNITYII_CASEDIAGONALVARIABLE_H
#define ETERNITYII_CASEDIAGONALVARIABLE_H

#include "../../../core/pathfinder/variable/VariableInterface.h"
#include "../../model/CaseModel.h"

class CaseDiagonalVariable: public VariableInterface
{
    CaseModel &_model;

    vector<vector<int>> coordinates;

public:

    CaseDiagonalVariable(CaseModel &model)
        : _model(model)
    {

        // mapping the coordinates
        coordinates.resize(_model.casesQte, vector<int>(2, 0));
        int depth = 0;
        for (int i = 0; i < _model.size; ++i) {
            for (int xi = i, yi = 0; yi <= i; --xi, ++yi) {
                coordinates[depth][0] = xi;
                coordinates[depth][1] = yi;
                ++depth;
            }
        }

        // seconde partie
        for (int i = 1; i < _model.size; ++i) {
            for (int xi = _model.size - 1, yi = i; yi < _model.size;
                 --xi, ++yi) {
                coordinates[depth][0] = xi;
                coordinates[depth][1] = yi;
                ++depth;
            }
        }
    }

    CaseData *next(int &depth) override
    {
        return new CaseData(coordinates[depth][0], coordinates[depth][1]);
    }

    const bool hasNext(int &depth) override
    {
        return depth < _model.casesQte &&
            _model.available[coordinates[depth][0]][coordinates[depth][1]];

    }
};


#endif //ETERNITYII_CASEDIAGONALVARIABLE_H
