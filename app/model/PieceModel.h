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

    vector<vector<bool>> isAvailableHistory;

    vector<vector<vector<vector<vector<bool>>>>> pieceCasesHistory;

public:
    int size;

    int nbPieces;

    vector<vector<int>> casesQte;

    vector<bool> isAvailable;

    vector<vector<vector<vector<bool>>>> pieceCases;

    void initialize(GameImportData &gameImportData);

    void accept(PieceData &pieceData, const int &depth);

    void accepted(CaseData &caseData, const int &depth);

    void discard(CaseData &caseData, PieceData &pieceData, const int &depth);

    void discarded(CaseData &caseData, const int &depth);

    void rollback(const int &from, const int &to);
};


#endif //ETERNITYII_PIECEMODEL_H
