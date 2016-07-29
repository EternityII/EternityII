#ifndef ETERNITYII_PIECEMODEL_H
#define ETERNITYII_PIECEMODEL_H

#include <vector>

#include "../../core/model/ModelInterface.h"
#include "../data/variable/CaseData.h"
#include "../data/value/PieceData.h"

using namespace std;

class PieceModel: public ModelInterface
{
    vector<vector<deque<PieceData> > > casesCountHistory;

    vector<vector<deque<PieceData> > > availableHistory;

    vector<vector<deque<pair<PieceData, CaseData> > > > pieceCasesHistory;

public:
    int size;

    int piecesQte;

    vector<vector<int> > casesCount;

    vector<bool> available;

    vector<vector<vector<vector<bool> > > > pieceCases;

    PieceModel(
        const GameImportData &gameImportData, EventManager &eventManager);

    void allow(
        const CaseData &caseData, const PieceData &pieceData, const int &depth);

    void addOne(const CaseData &caseData,
        const PieceData &pieceData);

    void denyOne(
        const CaseData &caseData,
        const PieceData &pieceData,
        const int &depth,
        const int &persistent);

    void deny(
        const CaseData &caseData, const int &depth, const int &persistent);

    void deny(
        const PieceData &pieceData, const int &depth, const int &persistent);

    void rollback(const int &depth, const bool &total = true);
};


#endif //ETERNITYII_PIECEMODEL_H
