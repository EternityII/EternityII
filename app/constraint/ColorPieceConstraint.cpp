#include "ColorPieceConstraint.h"
ColorPieceConstraint::ColorPieceConstraint(ColorModel &colorModel,
    PieceModel &pieceModel,
    EventManager &eventManager,
    GameImportData &gameImportData)
    : ConstraintInterface(eventManager), _first(colorModel), _second(pieceModel)
{
    _first.add(*this);
    _second.add(*this);

    borderMaxIndex = gameImportData.size * (gameImportData.size - 1);


    /*
     * Initialisation
     */

    bordureCases.resize(2 * borderMaxIndex);

    caseBordure.resize(gameImportData.size, // x
        vector<vector<BordureData> >(gameImportData.size, // y
            vector<BordureData>(4, BordureData(-1)))); // border n°-1

    colorPieces.resize(gameImportData.colorsQte,
        vector<deque<PieceData> >(4));

    pieceColors.resize(gameImportData.piecesQte, // pieceId
        vector<vector<ColorData> >(4, // pieceRotation
            vector<ColorData>(4))); // wanted face.

    /*
     * Default values
     */

    for (int x = 0; x < gameImportData.size - 1; ++x) {
        for (int y = 0; y < gameImportData.size - 1; ++y) {

            // vertical
            bordureCases[y * gameImportData.size + x].first.x = x;
            bordureCases[y * gameImportData.size + x].first.y = y;
            bordureCases[y * gameImportData.size + x].second.x = x + 1;
            bordureCases[y * gameImportData.size + x].second.y = y;


            // horizontal
            bordureCases[borderMaxIndex + (y * gameImportData.size + x)].first
                .x = x;
            bordureCases[borderMaxIndex + (y * gameImportData.size + x)].first
                .y = y;
            bordureCases[borderMaxIndex + (y * gameImportData.size + x)].second
                .x = x;
            bordureCases[borderMaxIndex + (y * gameImportData.size + x)].second
                .y = y + 1;


            caseBordure[x][y][2] = y * gameImportData.size + x;
            caseBordure[x + 1][y][0] = y * gameImportData.size + x;
            caseBordure[x][y][3] =
                borderMaxIndex + (y * gameImportData.size + x);
            caseBordure[x][y + 1][1] =
                borderMaxIndex + (y * gameImportData.size + x);
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

    const auto &caseDataFirst = bordureCases[bordureData.id].first;
    const auto &caseDataSecond = bordureCases[bordureData.id].second;

    if (bordureData.id < borderMaxIndex) { // vertical
        for (auto &iterator : colorPieces[colorData.id][2]) {
            _second.denyOne(caseDataFirst, iterator, depth, persistent);
        }

        for (auto &iterator : colorPieces[colorData.id][0]) {
            _second.denyOne(caseDataFirst, iterator, depth, persistent);
        }
    } else if (bordureData.id > borderMaxIndex) { // horizontal
        for (auto &iterator : colorPieces[colorData.id][3]) {
            _second.denyOne(caseDataFirst, iterator, depth, persistent);
        }

        for (auto &iterator : colorPieces[colorData.id][1]) {
            _second.denyOne(caseDataSecond, iterator, depth, persistent);
        }
    }
}

void ColorPieceConstraint::addOne(const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth, const int &persistent)
{
    // entrypoint : advice : the entrypoint is CasePieceConstraint, addOne action never goes up
    for (int rotation = 0; rotation < 4; ++rotation) {
        const auto &bordureData =
            caseBordure[caseData.x][caseData.y][rotation];
        const auto &colorData =
            pieceColors[pieceData.id][pieceData.rotation][rotation];

        _first.addOne(bordureData, colorData, depth, persistent);
    }
}

void ColorPieceConstraint::addOne(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth, const int &persistent)
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
            _second.addOne(caseDataFirst, iterator, depth, persistent);
        }

        for (auto &iterator : colorPieces[colorData.id][0]) {
            _second.addOne(caseDataFirst, iterator, depth, persistent);
        }
    } else if (bordureData.id > borderMaxIndex) { // horizontal
        for (auto &iterator : colorPieces[colorData.id][3]) {
            _second.addOne(caseDataFirst, iterator, depth, persistent);
        }

        for (auto &iterator : colorPieces[colorData.id][1]) {
            _second.addOne(caseDataSecond, iterator, depth, persistent);
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
