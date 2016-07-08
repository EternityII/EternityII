#ifndef ETERNITYII_PIECEMODEL_H
#define ETERNITYII_PIECEMODEL_H

#include <vector>

#include "../../core/model/ModelInterface.h"
#include "../data/variable/CaseData.h"
#include "../data/value/PieceData.h"

using namespace std;

class PieceModel: public ModelInterface
{
    vector<vector<vector<int>>> casesQteHistory;

    vector<vector<bool>> availableHistory;

    vector<vector<vector<vector<vector<bool>>>>> pieceCasesHistory;

public:
    int size;

    int nbPieces;

    vector<vector<int>> casesQte;

    vector<bool> available;

    vector<vector<vector<vector<bool>>>> pieceCases;

    void initialize(GameImportData &gameImportData);

    void accept(PieceData &pieceData, const int &depth);

    void accepted(CaseData &caseData, const int &depth);

    void discard(CaseData &caseData, PieceData &pieceData, const int &depth);

    void discarded(CaseData &caseData, const int &depth);

    /**
    * @param int const &depth, the depth to rollback
    *
    * Roll backs the given depth
    */
    void rollback(const int &depth);
};


#endif //ETERNITYII_PIECEMODEL_H
