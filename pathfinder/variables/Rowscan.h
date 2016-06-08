#ifndef ETERNITYII_ROWSCAN_H
#define ETERNITYII_ROWSCAN_H

#include "../../core/pathfinder/VariableInterface.h"

class Rowscan: public VariableInterface
{
public:
    Rowscan()
    { }

    void initialize(GameData &gameData)
    {
        variableDatas.resize(gameData.piecesQte);

        for (int i = 0; i < gameData.size; ++i) {
            for (int j = 0; j < gameData.size; ++j) {
                VariableData variableData(i, j);

                variableDatas[i * gameData.size + j] = variableData;
            }
        }
    }

    VariableData next(int &depth)
    {
        if (depth < variableDatas.size() && depth >= 0) {
            return variableDatas[depth];
        }
        else {
            return VariableData(false);
        }
    }

private:
    vector<VariableData> variableDatas;
};

#endif //ETERNITYII_ROWSCAN_H
