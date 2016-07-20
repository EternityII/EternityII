#ifndef ETERNITYII_FACEMODEL_H
#define ETERNITYII_FACEMODEL_H


#include "../../core/model/ModelInterface.h"
#include "BordureModel.h"
#include "../data/variable/BordureData.h"
#include "../data/value/PieceData.h"

class FaceModel: public ModelInterface
{
public:
    FaceModel(const GameImportData &gameImportData, EventManager &eventManager);

    /**
     * @param CaseData caseData, the case which was accepted
     * @param const int &depth,
     *
     * Informs the all the constraints about the change
     */
    void accept(const BordureData &bordureData,
        const FaceData &faceData,
        const int &depth);

    void accepted(const BordureData &bordureData, const int &depth);

    void accepted(const PieceData &pieceData, const int &depth);

    void discard(const BordureData &bordureData,
        const FaceData &faceData,
        const int &depth);

    void discarded(const BordureData &bordureData, const int &depth);

/**
     * Roll backs the given depth
     *
     * @param int const &depth, the depth to rollback
     */
    void rollback(const int &depth, const bool total = true);
};


#endif //ETERNITYII_FACEMODEL_H
