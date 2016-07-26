#ifndef ETERNITYII_CASEPESSIMISTVARIABLE_H
#define ETERNITYII_CASEPESSIMISTVARIABLE_H


#include "../../../core/pathfinder/variable/VariableInterface.h"
#include "../../model/CaseModel.h"

using namespace std;

class CasePessimistVariable: public VariableInterface
{
    CaseModel &_model;

    int iteratorX;
    int iteratorY;
    int max;

public:

    CasePessimistVariable(CaseModel &model)
        : _model(model), max(_model.casesQte * 4 + 1)
    {}

    CaseData *next(int &depth) override
    {
        return new CaseData(iteratorX, iteratorY);
    }

    const bool hasNext(int &depth) override
    {
        //because if has not next then it's impossible
        if (depth >= _model.casesQte) {
            return false;
        }
        int min = max;
        for (int xi = 0; xi < _model.size; ++xi) {
            for (int yi = 0; yi < _model.size; ++yi) {
                if (_model.available[xi][yi]) {
                    if (_model.pieceCount[xi][yi] == 0) {
                        return false;
                    } else if (_model.pieceCount[xi][yi] == 1) {
                        iteratorX = xi;
                        iteratorY = yi;
                        return true;
                    } else if (_model.pieceCount[xi][yi] < min) {
                        min = _model.pieceCount[xi][yi];
                        iteratorX = xi;
                        iteratorY = yi;
                    }
                }
            }
        }

        return min != _model.casesQte + 1;
    }
};


#endif //ETERNITYII_CASEPESSIMISTVARIABLE_H
