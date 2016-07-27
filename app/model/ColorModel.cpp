#include "ColorModel.h"
#include "../constraint/ColorPieceConstraint.h"
#include "../constraint/BordureColorConstraint.h"
#include "../../EternityII.h"
ColorModel::ColorModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    colorsQte = gameImportData.colorsQte;
    borduresQte = gameImportData.size * (gameImportData.size - 1) * 2;

    available.resize(colorsQte, true);
    availableHistory.resize(gameImportData.depth, vector<deque<ColorData> >(2));

    borduresCount.resize(colorsQte, borduresQte);
    borduresCountHistory.resize(gameImportData.depth,
        vector<deque<ColorData> >(2));

    colorBordures.resize(colorsQte, vector<int>(borduresQte));

    for (int bordureId = 0; bordureId < borduresQte; ++bordureId) {
        for (int colorId = 0; colorId < colorsQte; ++colorId) {
            colorBordures[colorId][bordureId] =
                gameImportData.colorCount[colorId];
        }
    }

}

void ColorModel::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    //entrypoint : unused : the entrypoint is CasePieceConstraint
    // TODO : minimal importance
}

void ColorModel::denyOne(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // if still available
    if (colorBordures[colorData.id][bordureData.id]) {
        colorBordures[colorData.id][bordureData.id] = false; // not anymore :)
        colorBorduresHistory[depth][persistent]
            .emplace_back(make_pair(colorData, bordureData));


        --colorBordures[colorData.id][bordureData.id];
        colorBorduresHistory[depth][persistent]
            .emplace_back(make_pair(colorData, bordureData));


        // the no-border zone
        if (colorBordures[colorData.id][bordureData.id] == 0) {
            --borduresCount[colorData.id];
            borduresCountHistory[depth][persistent]
                .emplace_back(colorData);


            // this border <--> color was denied
            // this is a very strong event
            // go my love, update the border please
            addDenyOneEvent(static_cast<BordureColorConstraint &>
                (*observers[EternityII::BOCO_CONSTRAINT]),
                bordureData,
                colorData,
                depth,
                persistent);

            // go my love update the piece <--> case
            addDenyOneEvent(static_cast<ColorPieceConstraint &>
                (*observers[EternityII::COPI_CONSTRAINT]),
                bordureData,
                colorData,
                depth,
                persistent);
        }
    }
}

void ColorModel::deny(const BordureData &bordureData,
    const int &depth,
    const int &persistent)
{
    //TODO : don't think it will be used : minimal importance
    // unused : dangerous : use with care

}

void ColorModel::deny(const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    //TODO : don't think it will be used : minimal importance
    // unused : dangerous : !! use with care

}

void ColorModel::rollback(const int &depth, const bool total)
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

    auto &qteQueue = borduresCountHistory[depth][type];
    while (not qteQueue.empty()) {
        ++borduresCount[qteQueue.back().id];
        qteQueue.pop_back();
    }

    auto &pcQueue = colorBorduresHistory[depth][type];
    while (not pcQueue.empty()) {
        ++colorBordures[pcQueue.back().first.id][pcQueue.back().second.id];
        pcQueue.pop_back();
    }
}
