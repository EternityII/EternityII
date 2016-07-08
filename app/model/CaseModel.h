#ifndef ETERNITYII_CASEMODEL_H
#define ETERNITYII_CASEMODEL_H

#include <vector>
#include "../../core/model/ModelInterface.h"
#include "../data/variable/CaseData.h"
#include "../data/value/PieceData.h"

using namespace std;

class CaseModel: public ModelInterface
{
    vector<vector<vector<int>>> piecesQteHistory;

    vector<vector<vector<bool>>> isAvailableHistory;

    vector<vector<vector<vector<vector<bool>>>>> casePiecesHistory;

public:
    int size;

    vector<vector<int>> piecesQte;

    vector<vector<bool>> isAvailable;

    vector<vector<vector<vector<bool>>>> casePieces;

    void initialize(GameImportData &gameImportData);

    /**
     * @param CaseData dataInterface, the case which was accepted
     * @param const int &depth,
     *
     * Informs the all the constraints about the change
     */
    void accept(CaseData &caseData, const int &depth);

    void accepted(PieceData &pieceData, const int &depth);

    void discard(CaseData &caseData, PieceData &pieceData, const int &depth);

    void discarded(PieceData &pieceData, const int &depth);

    void rollback(const int &depth);
};


#endif //ETERNITYII_CASEMODEL_H
