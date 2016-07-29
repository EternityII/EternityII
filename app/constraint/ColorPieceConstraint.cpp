#include "ColorPieceConstraint.h"
ColorPieceConstraint::ColorPieceConstraint(ColorModel &colorModel,
    PieceModel &pieceModel,
    EventManager &eventManager,
    GameImportData &gameImportData)
    : ConstraintInterface(eventManager), _first(colorModel), _second(pieceModel)
{
    _first.add(*this);
    _second.add(*this);

    const auto size = gameImportData.size;
    borderMaxIndex = 2 * size * (size - 1);


    /*
    * Initialisation
    */

    bordureCases.resize(2 * borderMaxIndex);

    caseBordure.resize(size, // x
        vector<vector<BordureData> >(size, // y
            vector<BordureData>(4, BordureData(-1)))); // border n°-1

    colorPieces.resize(gameImportData.colorsQte,
        vector<deque<PieceData> >(4));

    pieceColors.resize(gameImportData.piecesQte, // pieceId
        vector<vector<ColorData> >(4, // pieceRotation
            vector<ColorData>(4))); // wanted face.

    /*
     * Default values
     */
    // bordureCases & caseBordure
    // could be put together but won't for cohesion reason
    // vertical borders
    auto borderIndex = 0;
    for (int yi = 0; yi < size; ++yi) {
        for (int xi = 0; xi < size - 1; ++xi) {
            // right side
            bordureCases[borderIndex].x = xi;
            bordureCases[borderIndex].y = yi;
            caseBordure[xi][yi][2].id = borderIndex;
            ++borderIndex;

            //leftside
            bordureCases[borderIndex].x = xi + 1;
            bordureCases[borderIndex].y = yi;
            caseBordure[xi + 1][yi][0].id = borderIndex;
            ++borderIndex;
        }
    }

    // horizontal borders
    for (int yi = 0; yi < size - 1; ++yi) {
        for (int xi = 0; xi < size; ++xi) {
            // topside
            bordureCases[borderIndex].x = xi;
            bordureCases[borderIndex].y = yi;
            caseBordure[xi][yi][3].id = borderIndex;
            ++borderIndex;

            //bottomside
            bordureCases[borderIndex].x = xi;
            bordureCases[borderIndex].y = yi + 1;
            caseBordure[xi][yi + 1][1].id = borderIndex;
            ++borderIndex;
        }
    }


    // colorPieces & pieceColors
    for (int pieceId = 0; pieceId < gameImportData.piecesQte; ++pieceId) {
        for (int rotation = 0; rotation < 4; ++rotation) {
            for (int position = 0; position < 4; ++position) {
                const auto colorId =
                    gameImportData.pieces[pieceId]->colors[rotation][position];
                // this color at this specific position has this piece
                colorPieces[colorId][position].emplace_back(pieceId, rotation);
                pieceColors[pieceId][rotation][position].id = colorId;
            }
        }
    }

}

void ColorPieceConstraint::allow(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{
    //entrypoint : unused : the entrypoint is CasePieceConstraint
    // TODO : minimal importance
    //_first.allow(bordureData, colorData, depth);
    // all the pieces having this color are allowed
    //_second.allow(caseData, pieceData, depth);

    // entrypoint : unused : to be uncommented if the entrypoint is this Constraint
    /* // entrypoint : advice : comment this if the entrypoint is not this constraint
    while(not eventManager.empty()){
        eventManager.process();
    }*/

}

void ColorPieceConstraint::allow(const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth)
{
    // entrypoint : unused : the entrypoint is CasePieceConstraint
    // TODO : minimal importance
}

void ColorPieceConstraint::denyOne(const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth, const int &persistent)
{
    for (int rotation = 0; rotation < 4; ++rotation) {
        const auto &bordureData =
            caseBordure[caseData.x][caseData.y][rotation];
        const auto &colorData =
            pieceColors[pieceData.id][pieceData.rotation][rotation];

        _first.denyOne(bordureData, colorData, depth, persistent);
    }

}

void ColorPieceConstraint::denyOne(const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth, const int &persistent)
{
    if (bordureData.id == -1) {
        return;
    }

    const auto &caseDataFirst =
        bordureCases[bordureData.id - (bordureData.id % 2)];
    const auto &caseDataSecond =
        bordureCases[bordureData.id + (bordureData.id + 1) % 2];

    if (bordureData.id < borderMaxIndex) { // vertical
        for (auto &iterator : colorPieces[colorData.id][2]) {
            _second.denyOne(caseDataFirst, iterator, depth, persistent);
        }

        for (auto &iterator : colorPieces[colorData.id][0]) {
            _second.denyOne(caseDataFirst, iterator, depth, persistent);
        }
    } else if (bordureData.id >= borderMaxIndex) { // horizontal
        for (auto &iterator : colorPieces[colorData.id][3]) {
            _second.denyOne(caseDataFirst, iterator, depth, persistent);
        }

        for (auto &iterator : colorPieces[colorData.id][1]) {
            _second.denyOne(caseDataSecond, iterator, depth, persistent);
        }
    }
}

void ColorPieceConstraint::addOne(const CaseData &caseData,
    const PieceData &pieceData)
{
    // entrypoint : advice : the entrypoint is CasePieceConstraint, addOne action never goes up
    for (int rotation = 0; rotation < 4; ++rotation) {
        const auto &bordureData =
            caseBordure[caseData.x][caseData.y][rotation];
        const auto &colorData =
            pieceColors[pieceData.id][pieceData.rotation][rotation];

        _first.addOne(bordureData, colorData);
    }
}

void ColorPieceConstraint::addOne(
    const BordureData &bordureData,
    const ColorData &colorData)
{
    // entrypoint : unused : the entrypoint is CasePieceConstraint, addOne action never goes up
    /*
    if (bordureData.id == -1) {
        return;
    }

    const auto &caseDataFirst = bordureCases[bordureData.id].first;
    const auto &caseDataSecond = bordureCases[bordureData.id].second;

    if (bordureData.id < borderMaxIndex) { // vertical
        for (auto &iterator : colorPieces[colorData.id][2]) {
            _second.addOne(caseDataFirst, iterator);
        }

        for (auto &iterator : colorPieces[colorData.id][0]) {
            _second.addOne(caseDataFirst, iterator);
        }
    } else if (bordureData.id > borderMaxIndex) { // horizontal
        for (auto &iterator : colorPieces[colorData.id][3]) {
            _second.addOne(caseDataFirst, iterator);
        }

        for (auto &iterator : colorPieces[colorData.id][1]) {
            _second.addOne(caseDataSecond, iterator);
        }
    }
     */

}

void ColorPieceConstraint::deny(const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // TODO : minimal importance
    // unused : dangerous : won't be used, the effects are too big
}

void ColorPieceConstraint::deny(const PieceData &pieceData,
    const int &depth,
    const int &persistent)
{
    // TODO : minimal importance
    // unused : dangerous : won't be used, the effects are too big
}
