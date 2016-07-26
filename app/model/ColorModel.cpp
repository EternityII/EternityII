#include "ColorModel.h"
#include "../constraint/ColorPieceConstraint.h"
#include "../constraint/BordureColorConstraint.h"
#include "../../EternityII.h"
ColorModel::ColorModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    //TODO : IMPORTANT
}

void ColorModel::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    //entrypoint : not used because the entrypoint is CasePieceConstraint
    // TODO : minimal importance
}

void ColorModel::denyOne(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // if still available
    if (colorBordures[colorData.id][bordureData.id]) {
        colorBordures[colorData.id][bordureData.id] = false;
        colorBorduresHistory[depth][persistent]
            .emplace_back(make_pair(colorData, bordureData));

        --borduresCount[colorData.id];
        borduresCountHistory[depth][persistent]
            .emplace_back(colorData);

        if (borduresCount[colorData.id] == 0) {
            colorBordures[colorData.id][bordureData.id] = false;
            colorBorduresHistory[depth][persistent]
                .emplace_back(make_pair(colorData, bordureData));


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
    // DANGEROUS !! use with care

}

void ColorModel::deny(const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    //TODO : don't think it will be used : minimal importance
    // DANGEROUS !! use with care

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
        colorBordures[pcQueue.back().first.id][pcQueue.back().second.id] = true;
        pcQueue.pop_back();
    }
}
