#include "BordureModel.h"
#include "../../EternityII.h"
#include "../constraint/BordureColorConstraint.h"
#include "../constraint/BordureCaseConstraint.h"

BordureModel::BordureModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    borduresQte = gameImportData.size * (gameImportData.size - 1) * 2;
    colorsQte = gameImportData.colorsQte;

    available.resize(borduresQte, true);
    availableHistory.resize(gameImportData.depth,
        vector<deque<BordureData>>(2));

    colorsCount.resize(borduresQte, colorsQte);
    colorsCountHistory.resize(gameImportData.depth,
        vector<deque<BordureData>>(2));

    bordureColors.resize(borduresQte, vector<int>(colorsQte, 0));
    bordureColorsHistory.resize(gameImportData.depth,
        vector<deque<pair<BordureData, ColorData> > >(2));

    for (int bordureId = 0; bordureId < borduresQte; ++bordureId) {
        for (int colorId = 0; colorId < colorsQte; ++colorId) {
            bordureColors[bordureId][colorId] =
                gameImportData.colorCount[colorId];
        }
    }
}

void BordureModel::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    // entrypoint : unused : the entrypoint is CasePiece
    if (available[bordureData.id]) {
        for (int colorId = 0; colorId < colorsQte; ++colorId) {
            if (colorId != colorData.id) {
                ColorData colorDataPartialDeny(colorId);
                // yep that's good, everything else is denied
                denyOne(bordureData, colorDataPartialDeny, depth, TRANSITORY);
            }
        }

        available[bordureData.id] = false;
        availableHistory[depth][TRANSITORY].emplace_back(bordureData);

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
    if (bordureData.id != -1
        && bordureColors[bordureData.id][colorData.id] != 0) {
        --bordureColors[bordureData.id][colorData.id];
        bordureColorsHistory[depth][persistent]
            .emplace_back(make_pair(bordureData, colorData));

        // HAHA !! The color is not here anymoooroe !
        if (bordureColors[bordureData.id][colorData.id] == 0) {
            --colorsCount[bordureData.id];
            colorsCountHistory[depth][persistent]
                .emplace_back(bordureData);

            // this border <--> color was denied
            // this is a very strong event
            addDenyOneEvent(static_cast<BordureColorConstraint &>
                (*observers[0]),
                bordureData,
                colorData,
                depth,
                persistent);

            addDenyOneEvent(static_cast<BordureCaseConstraint &>
                (*observers[1]),
                bordureData,
                colorData,
                depth,
                persistent);
        }
    }
}

void BordureModel::addOne(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // x time action no consequence (blind action)
    if (bordureData.id != -1) {
        // this one is à no check so be careful
        if (bordureColors[bordureData.id][colorData.id] == 0) {
            // first time having this color :)
            ++colorsCount[bordureData.id];
        }

        ++bordureColors[bordureData.id][colorData.id];
    }
}

void BordureModel::deny(const BordureData &bordureData,
    const int &depth,
    const int &persistent)
{
    // unused : dangerous : well that was f****** scary
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
    // unused : dangerous : use with care
    for (int bordureId = 0; bordureId < borduresQte; ++bordureId) {
        if (available[bordureId]) {
            BordureData bordureData(bordureId);

            denyOne(bordureData, colorData, depth, persistent);
        }
    }
}

void BordureModel::rollback(const int &depth, const bool &total/* = true */)
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
        ++bordureColors[pcQueue.back().first.id][pcQueue.back().second.id];
        pcQueue.pop_back();
    }
}

