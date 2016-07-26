#include "BordureModel.h"
#include "../../EternityII.h"
#include "../constraint/BordureColorConstraint.h"
#include "../constraint/BordureCaseConstraint.h"

BordureModel::BordureModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    //TODO : IMPORTANT
}

void BordureModel::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    // entrypoint : Won't be used : the entrypoint is CasePiece
    if (available[bordureData.id]) {
        for (int colorId = 0; colorId < borduresQte; ++colorId) {
            if (colorId != colorData.id) {
                ColorData colorDataPartialDeny(colorId);
                // yep that's good, everything else is denied
                denyOne(bordureData, colorDataPartialDeny, depth, TRANSITORY);
            }
        }

        available[bordureData.id] = false;
        availableHistory[depth][TRANSITORY].emplace_back(bordureData);

        --colorsCount[bordureData.id];
        colorsCountHistory[depth][TRANSITORY].emplace_back(bordureData);

        // this bordure isn't available anymore so we notify the colorModel
        addDenyEvent(static_cast<BordureColorConstraint &>
            (*observers[EternityII::BOCO_CONSTRAINT]),
            bordureData, depth, TRANSITORY
        );
    }
}

void BordureModel::denyOne(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    if (bordureColors[bordureData.id][colorData.id]) {
        bordureColors[bordureData.id][colorData.id] = false;
        bordureColorsHistory[depth][persistent]
            .emplace_back(make_pair(bordureData, colorData));

        --colorsCount[bordureData.id];
        colorsCountHistory[depth][persistent]
            .emplace_back(bordureData);

        // HAHA !! The color is not here anymoooroe !
        if (colorsCount[bordureData.id] == 0) {
            bordureColors[bordureData.id][colorData.id] = false;
            bordureColorsHistory[depth][persistent]
                .emplace_back(make_pair(bordureData, colorData));

            // this border <--> color was denied
            // this is a very strong event
            addDenyOneEvent(static_cast<BordureColorConstraint &>
                (*observers[EternityII::BOCO_CONSTRAINT]),
                bordureData,
                colorData,
                depth,
                persistent);

            addDenyOneEvent(static_cast<BordureCaseConstraint &>
                (*observers[EternityII::BOCA_CONSTRAINT]),
                bordureData,
                colorData,
                depth,
                persistent);
        }
    }
}

void BordureModel::deny(const BordureData &bordureData,
    const int &depth,
    const int &persistent)
{
    // entrypoint : CasePieceConstraint
    // DANGEROUS !! use with care
    if (available[bordureData.id]) {
        for (int colorId = 0; colorId < borduresQte; ++colorId) {
            ColorData colorData(colorId);

            denyOne(bordureData, colorData, depth, persistent);
        }
    }
}

void BordureModel::deny(const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // DANGEROUS !! use with care
    for (int bordureId = 0; bordureId < borduresQte; ++bordureId) {
        if (available[bordureId]) {
            BordureData bordureData(bordureId);

            denyOne(bordureData, colorData, depth, persistent);
        }
    }
}

void BordureModel::rollback(const int &depth, const bool total/* = true */)
{
    int type;
    if (total) {
        type = PERSISTENT;
        rollback(depth, false);
    } else {
        type = TRANSITORY;
    }

    auto &availQueue = availableHistory[depth][type];
    while (not availQueue.empty()) {
        available[availQueue.back().id] = true;
        availQueue.pop_back();
    }

    auto &qteQueue = colorsCountHistory[depth][type];
    while (not qteQueue.empty()) {
        ++colorsCount[qteQueue.back().id];
        qteQueue.pop_back();
    }

    auto &pcQueue = bordureColorsHistory[depth][type];
    while (not pcQueue.empty()) {
        bordureColors[pcQueue.back().first.id][pcQueue.back().second.id] = true;
        pcQueue.pop_back();
    }
}

