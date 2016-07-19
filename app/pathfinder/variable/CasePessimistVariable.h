#ifndef ETERNITYII_CASEPESSIMISTVARIABLE_H
#define ETERNITYII_CASEPESSIMISTVARIABLE_H


#include "../../../core/pathfinder/variable/VariableInterface.h"
#include "../../model/CaseModel.h"

using namespace std;

class CasePessimistVariable: public VariableInterface
{
    CaseModel *_model;

    int iteratorX;
    int iteratorY;

public:

    CasePessimistVariable(CaseModel &model)
    {
        this->_model = &model;
    }

    CaseData *next(int &depth) override
    {
        return new CaseData(iteratorX, iteratorY);
    }

    const bool hasNext(int &depth) override
    {
        //because if has not next then it's impossible
        if (depth >= _model->nbCases) {
            return false;
        }
        int min = _model->nbCases * 4 + 1;
        for (int xi = 0; xi < _model->size; ++xi) {
            for (int yi = 0; yi < _model->size; ++yi) {
                if (_model->available[xi][yi]) {
                    if (_model->piecesQte[xi][yi] == 0) {
                        return false;
                    } else if (_model->piecesQte[xi][yi] == 1) {
                        iteratorX = xi;
                        iteratorY = yi;
                        return true;
                    } else if (_model->piecesQte[xi][yi] < min) {
                        min = _model->piecesQte[xi][yi];
                        iteratorX = xi;
                        iteratorY = yi;
                    }
                }
            }
        }

        return min != _model->nbCases + 1;
    }
};


#endif //ETERNITYII_CASEPESSIMISTVARIABLE_H
