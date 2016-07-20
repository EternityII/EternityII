#ifndef ETERNITYII_BORDUREMODEL_H
#define ETERNITYII_BORDUREMODEL_H


#include "../../core/model/ModelInterface.h"
#include "../data/variable/BordureData.h"
#include "../data/variable/CaseData.h"
#include "../data/value/FaceData.h"

class BordureModel: public ModelInterface
{
public:
    BordureModel(
        const GameImportData &gameImportData, EventManager &eventManager);

    /**
     * @param CaseData caseData, the case which was accepted
     * @param const int &depth,
     *
     * Informs the all the constraints about the change
     */
    void accept(const BordureData &bordureData,
        const FaceData &faceData,
        const int &depth);

    void accepted(const FaceData &faceData, const int &depth);

    void accepted(const CaseData &caseData, const int &depth);

    void discard(const BordureData &bordureData,
        const FaceData &faceData,
        const int &depth);

    void discarded(const FaceData &faceData, const int &depth);

/**
     * Roll backs the given depth
     *
     * @param int const &depth, the depth to rollback
     */
    void rollback(const int &depth, const bool total = true);
};


#endif //ETERNITYII_BORDUREMODEL_H
