#include "ColorModel.h"
#include "../constraint/ColorPieceConstraint.h"
#include "../constraint/BordureColorConstraint.h"
ColorModel::ColorModel(
    const GameImportData &gameImportData, EventManager &eventManager)
    : ModelInterface(eventManager)
{
    colorsQte = gameImportData.colorsQte;
    borduresQte = gameImportData.size * (gameImportData.size - 1) * 4;

    // default values
    available.resize(colorsQte, false);

    borduresCount.resize(colorsQte, 0);

    colorBordures.resize(colorsQte, vector<int>(borduresQte));

    // History
    availableHistory.resize(gameImportData.depth, vector<deque<ColorData> >(2));
    borduresCountHistory.resize(gameImportData.depth,
        vector<deque<ColorData> >(2));
    colorBorduresHistory.resize(gameImportData.depth,
        vector<deque<pair<ColorData, BordureData> > >(2));

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
    if (bordureData.id != -1
        && colorBordures[colorData.id][bordureData.id] != 0) {

        --colorBordures[colorData.id][bordureData.id];
        colorBorduresHistory[depth][persistent]
            .emplace_back(make_pair(colorData, bordureData));


        // the no-border zone
        if (colorBordures[colorData.id][bordureData.id] == 0) {
            --borduresCount[colorData.id];
            borduresCountHistory[depth][persistent]
                .emplace_back(colorData);

            BordureData bordureDataOther(
                bordureData.id % 2 == 0 ?
                bordureData.id + 1 : bordureData.id - 1);

            // make it disapear on the other border !
            for (int colors = 0;
                 colors < colorBordures[colorData.id][bordureDataOther.id];
                 ++colors) {

                static_cast<BordureColorConstraint &>(*observers[0])
                    .denyOne(bordureDataOther, colorData, depth, persistent);
            }


            // this border <--> color was denied
            // this is a very strong event
            // go my love, update the border please
            static_cast<BordureColorConstraint &>(*observers[0])
                .denyOne(bordureData, colorData, depth, persistent);

            // go my love update the piece <--> case
            static_cast<ColorPieceConstraint &>(*observers[1])
                .denyOne(bordureData, colorData, depth, persistent);
        }
    }
}

void ColorModel::addOne(const BordureData &bordureData,
    const ColorData &colorData)
{

    if (bordureData.id != -1) { // just to be sure
        // one time action
        if (not available[colorData.id]) {
            available[colorData.id] = true;
        }

        // x time action no consequence (blind action)
        if (colorBordures[colorData.id][bordureData.id] == 0) {
            // first time having this border :)
            ++borduresCount[colorData.id];
        }

        ++colorBordures[colorData.id][bordureData.id];
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

void ColorModel::rollback(const int &depth, const bool &total /* = true */)
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
