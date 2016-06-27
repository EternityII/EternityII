#ifndef ETERNITYII_CASEMODEL_H
#define ETERNITYII_CASEMODEL_H

#include <vector>
#include "../../core/model/ModelInterface.h"
#include "../data/variable/CaseData.h"

using namespace std;

class CaseModel: public ModelInterface
{
    vector<vector<vector<int>>> piecesQteHistory;

    vector<vector<vector<vector<vector<bool>>>>> piecesPossibleHistory;

    vector<vector<vector<int>>> isAvailableHistory;

public:
    vector<vector<int>> piecesQte;

    vector<vector<vector<vector<bool>>>> piecesPossible;

    vector<vector<int>> isAvailable;

    void initialize(GameImportData &gameImportData);

    void accept(DataInterface &dataInterface, const int &depth);

    void discard(DataInterface &dataInterface, const int &depth);

    void rollback(const int &depth);
};


#endif //ETERNITYII_CASEMODEL_H
