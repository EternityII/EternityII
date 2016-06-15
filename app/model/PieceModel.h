#ifndef ETERNITYII_PIECEMODEL_H
#define ETERNITYII_PIECEMODEL_H

#include <vector>
#include "../../core/model/ModelInterface.h"

using namespace std;

class PieceModel: public ModelInterface
{

    vector<vector<int>> casesQteHistory;

    vector<vector<vector<vector<vector<bool>>>>> casesPossibleHistory;

    vector<vector<bool>> isAvailableHistory;

public:
    vector<int> casesQte;

    vector<vector<vector<vector<bool>>>> casesPossible;

    vector<bool> isAvailable;

    void initialize(GameImportData &gameImportData);

    void rollback(const int &depth);

    void accept(DataInterface &dataInterface);

    void discard(DataInterface &dataInterface);
};


#endif //ETERNITYII_PIECEMODEL_H
