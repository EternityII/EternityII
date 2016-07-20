#ifndef ETERNITYII_BORDUREFACECONSTRAINT_H
#define ETERNITYII_BORDUREFACECONSTRAINT_H

#include "../../core/ConstraintInterface.h"
#include "../model/BordureModel.h"
#include "../model/FaceModel.h"

class BordureFaceConstraint: public ConstraintInterface
{
    BordureModel &_first;
    FaceModel &_second;
public:
    BordureFaceConstraint(BordureModel &bordureModel,
        FaceModel &faceModel,
        EventManager &eventManager);

    /**
     * @param BordureData &bordureData, the variable to apply
     * @param FaceData &faceData, the value to apply
     *
     * applies the data for this constraint
     */
    void accept(const BordureData &bordureData,
        const FaceData &faceData,
        const int &depth);

    /**
     * @param BordureData &bordureData, the variable to apply
     * @param FaceData &faceData, the value to apply
     *
     * discards this variable<->value association
     */
    void discard(const BordureData &bordureData,
        const FaceData &faceData,
        const int &depth);

    /**
     * @param BordureData &bordureData, variable data
     *
     * propagates (applies) the data to FaceModel from BordureModel
     */
    void accepted(const BordureData &bordureData, const int &depth);

    /**
     * @param FaceData &faceData, value data
     *
     * propagates (applies) the data to BordureModel from FaceModel
     */
    void accepted(const FaceData &faceData, const int &depth);

    void discarded(const FaceData &faceData, const int &depth);

    void discarded(const BordureData &bordureData, const int &depth);
};


#endif //ETERNITYII_BORDUREFACECONSTRAINT_H
