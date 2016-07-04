#ifndef ETERNITYII_PIECEMODEL_H
#define ETERNITYII_PIECEMODEL_H

#include <vector>

#include "../../core/model/ModelInterface.h"
#include "../data/variable/CaseData.h"
#include "../data/value/PieceData.h"

using namespace std;

class PieceModel: public ModelInterface<CaseData, PieceData>
{
    int nbPieces;
    int size;

    vector<vector<vector<int>>> casesQteHistory;

    vector<vector<vector<bool>>> isAvailableHistory;

    vector<vector<vector<vector<vector<bool>>>>> pieceCasesHistory;

public:
    vector<vector<int>> casesQte;

    vector<vector<bool>> isAvailable;

    vector<vector<vector<vector<bool>>>> pieceCases;

    void initialize(GameImportData &gameImportData);

    void accept(CaseData &caseData, const int &depth);

    void accept(PieceData &pieceData, const int &depth);

    void discard(CaseData &caseData, const int &depth);
    void discard(PieceData &pieceData, const int &depth);

    void rollback(const int &from, const int &to);
};


#endif //ETERNITYII_PIECEMODEL_H
