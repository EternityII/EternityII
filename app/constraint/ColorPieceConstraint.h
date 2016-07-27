#ifndef ETERNITYII_COLORPIECECONSTRAINT_H
#define ETERNITYII_COLORPIECECONSTRAINT_H


#include "../../core/ConstraintInterface.h"
#include "../model/ColorModel.h"
#include "../model/PieceModel.h"

class ColorPieceConstraint: public ConstraintInterface
{
    //! rewriting #first
    ColorModel &_first;

    //! rewriting #second
    PieceModel &_second;

    //! bordureCase contains the cases on both sides
    vector<pair<CaseData, CaseData> > bordureCases;

    //! contains the data of each border
    vector<vector<vector<BordureData> > > caseBordure;

    //! list of all the pieces containing this color at the each rotation
    vector<vector<deque<PieceData> > > colorPieces;

    //! each color at each rotation of the piece
    vector<vector<vector<ColorData> > > pieceColors;

    //! max index of the border
    int borderMaxIndex;
public:

    ColorPieceConstraint(ColorModel &colorModel,
        PieceModel &pieceModel,
        EventManager &eventManager,
        GameImportData &gameImportData);

    void allow(const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth);

    void allow(const CaseData &caseData,
        const PieceData &pieceData,
        const int &depth);

    void denyOne(
        const BordureData &bordureData,
        const ColorData &colorData,
        const int &depth, const int &persistent);

    void denyOne(
        const CaseData &caseData,
        const PieceData &pieceData,
        const int &depth,
        const int &persistent);

    void deny(
        const ColorData &colorData, const int &depth, const int &persistent);
    void deny(
        const PieceData &pieceData, const int &depth, const int &persistent);
};


#endif //ETERNITYII_COLORPIECECONSTRAINT_H
