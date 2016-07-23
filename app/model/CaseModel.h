#ifndef ETERNITYII_CASEMODEL_H
#define ETERNITYII_CASEMODEL_H

#include <vector>
#include "../../core/model/ModelInterface.h"
#include "../data/variable/CaseData.h"
#include "../data/value/PieceData.h"

using namespace std;

class CaseModel: public ModelInterface
{
    vector<vector<deque<CaseData> > > piecesQteHistory;

    vector<vector<deque<CaseData> > > availableHistory;

    vector<vector<deque<pair<CaseData, PieceData> > > > casePiecesHistory;

public:
    int size;
    int casesQte;

    vector<vector<int>> piecesQte;

    vector<vector<bool>> available;

    vector<vector<vector<vector<bool>>>> casePieces;

    CaseModel(const GameImportData &gameImportData, EventManager &eventManager);

    void allow(
        const CaseData &caseData, const PieceData &pieceData, const int &depth);

    void denyOne(
        const CaseData &caseData,
        const PieceData &pieceData,
        const int &depth,
        const int &persistent);

    void deny(const PieceData &pieceData,
        const int &depth,
        const int &persistent);

    void deny(const CaseData &caseData,
        const int &depth,
        const int &persistent);

    void rollback(const int &depth, const bool &total = true);
};


#endif //ETERNITYII_CASEMODEL_H
