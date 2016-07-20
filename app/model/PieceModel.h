#ifndef ETERNITYII_PIECEMODEL_H
#define ETERNITYII_PIECEMODEL_H

#include <vector>

#include "../../core/model/ModelInterface.h"
#include "../data/variable/CaseData.h"
#include "../data/value/PieceData.h"

using namespace std;

class PieceModel: public ModelInterface
{
    vector<vector<deque<PieceData>>> casesQteHistory;

    vector<vector<deque<PieceData>>> availableHistory;

    vector<vector<deque<pair<PieceData, CaseData>>>> pieceCasesHistory;

public:
    int size;

    int nbPieces;

    vector<vector<int>> casesQte;

    vector<bool> available;

    vector<vector<vector<vector<bool>>>> pieceCases;

    PieceModel(
        const GameImportData &gameImportData, EventManager &eventManager);

    void accept(
        const CaseData &caseData, const PieceData &pieceData, const int &depth);

    void discard(
        const CaseData &caseData, const PieceData &pieceData, const int &depth);

    void accepted(const CaseData &caseData, const int &depth);

    void accepted(const PieceData &pieceData, const int &depth);

    void discarded(const CaseData &caseData, const int &depth);
    /**
    * @param int const &depth, the depth to rollback
    *
    * Roll backs the given depth
    */
    void rollback(const int &depth, const bool &total = true);
};


#endif //ETERNITYII_PIECEMODEL_H
