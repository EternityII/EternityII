#ifndef ETERNITYII_FACEPIECECONSTRAINT_H
#define ETERNITYII_FACEPIECECONSTRAINT_H


#include "../../core/ConstraintInterface.h"
#include "../model/FaceModel.h"
#include "../model/PieceModel.h"

class FacePiececonstraint: public ConstraintInterface
{
    FaceModel &_first;
    PieceModel &_second;
public:
    FacePiececonstraint(FaceModel &faceModel,
        PieceModel &pieceModel,
        EventManager &eventManager);

    /**
 * @param FaceData &faceData, the variable to apply
 * @param PieceData &pieceData, the value to apply
 *
 * applies the data for this constraint
 */
    void accept(const FaceData &faceData,
        const PieceData &pieceData,
        const int &depth);

    /**
     * @param FaceData &faceData, the variable to apply
     * @param PieceData &pieceData, the value to apply
     *
     * discards this variable<->value association
     */
    void discard(const FaceData &faceData,
        const PieceData &pieceData,
        const int &depth);

    /**
     * @param FaceData &faceData, variable data
     *
     * propagates (applies) the data to FaceModel from BordureModel
     */
    void accepted(const FaceData &faceData, const int &depth);

    /**
     * @param PieceData &pieceData, value data
     *
     * propagates (applies) the data to BordureModel from FaceModel
     */
    void accepted(const PieceData &pieceData, const int &depth);

    void discarded(const PieceData &pieceData, const int &depth);

    void discarded(const FaceData &faceData, const int &depth);
};


#endif //ETERNITYII_FACEPIECECONSTRAINT_H
