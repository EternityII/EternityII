#include "BordureModel.h"
#include "../../EternityII.h"
#include "../constraint/BordureColorConstraint.h"

BordureModel::BordureModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    //TODO
}

void BordureModel::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    if (available[bordureData.id]) {
        for (int colorId = 0; colorId < borduresQte; ++colorId) {
            if (colorId != colorData.id) {
                ColorData colorDataPartialDeny(colorId);

                denyOne(bordureData, colorDataPartialDeny, depth, TRANSITORY);
            }
        }

        available[bordureData.id] = false;
        availableHistory[depth][TRANSITORY].emplace_back(bordureData);

        --colorsQte[bordureData.id];
        colorsQteHistory[depth][TRANSITORY].emplace_back(bordureData);

        // this edge isn't available anymore so we notify the colorModel
        addDenyEvent(static_cast<BordureColorConstraint &>
            (*observers[EternityII::CPCONSTRAINT]),
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

        --colorsQte[bordureData.id];
        colorsQteHistory[depth][persistent]
            .emplace_back(bordureData);
    }
}

void BordureModel::deny(const BordureData &bordureData,
    const int &depth,
    const int &persistent)
{
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
    while (!availQueue.empty()) {
        available[availQueue.back().id] = true;
        availQueue.pop_back();
    }

    auto &qteQueue = colorsQteHistory[depth][type];
    while (!qteQueue.empty()) {
        ++colorsQte[qteQueue.back().id];
        qteQueue.pop_back();
    }

    auto &pcQueue = bordureColorsHistory[depth][type];
    while (!pcQueue.empty()) {
        bordureColors[pcQueue.back().first.id][pcQueue.back().second.id] = true;
        pcQueue.pop_back();
    }
}

