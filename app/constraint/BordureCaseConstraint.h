#ifndef ETERNITYII_BORDURECASECONSTRAINT_H
#define ETERNITYII_BORDURECASECONSTRAINT_H

#include "../../core/ConstraintInterface.h"
#include "../model/BordureModel.h"
#include "../model/CaseModel.h"

class BordureCaseConstraint: public ConstraintInterface
{
    //! rewriting #first
    BordureModel &_first;

    //! rewriting #second
    CaseModel &_second;

    //! bordureCase contains the cases on both sides
    vector<pair<CaseData, CaseData> > bordureCases;

    //! contains the data of each border
    vector<vector<vector<BordureData> > > caseBordure;

    //! list of all the pieces containing this color at the each rotation
    vector<vector<deque<PieceData> > > colorPieces;

    //! each color at each rotation of the piece
    vector<vector<vector<ColorData> > > pieceColors;

    //! max index when the border becomes horizontal
    int borderMaxIndex;
public:
    BordureCaseConstraint(BordureModel &bordureModel,
        CaseModel &caseModel,
        EventManager &eventManager,
        GameImportData &gameImportData);

    void allow(
        const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth);

    void allow(
        const CaseData &caseData, const PieceData &pieceData, const int &depth);

    void denyOne(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth,
        const int &persistent);

    void denyOne(const CaseData &caseData,
        const PieceData &pieceData,
        const int &depth,
        const int &persistent);

    void deny(const BordureData &bordureData,
        const int &depth,
        const int &persistent);

    void deny(
        const CaseData &caseData, const int &depth, const int &persistent);

};


#endif //ETERNITYII_BORDURECASECONSTRAINT_H
