#include "BordureCaseConstraint.h"
BordureCaseConstraint::BordureCaseConstraint(BordureModel &bordureModel,
    CaseModel &caseModel,
    EventManager &eventManager,
    GameImportData &gameImportData)
    : ConstraintInterface(eventManager), _first(bordureModel),
      _second(caseModel)
{
    _first.add(*this);
    _second.add(*this);

    // TODO all the equivalence piece[rotation] <--> colors.id and bordure.id <--> case.id

    const auto size = gameImportData.size;
    borderMaxIndex = size * (size - 1);


    /* 
     * Initialisation
     */

    bordureCases.resize(2 * borderMaxIndex);

    caseBordure.resize(size, // x
        vector<vector<BordureData> >(size, // y
            vector<BordureData>(4, BordureData(-1)))); // border n°

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
    for (int xi = 0; xi < size - 1; ++xi) {
        for (int yi = 0; yi < size; ++yi) {
            const auto index = xi * size + yi;
            bordureCases[index].first.x = xi;
            bordureCases[index].first.y = yi;
            bordureCases[index].second.x = xi + 1;
            bordureCases[index].second.y = yi;

            // right side
            caseBordure[xi][yi][2].id = index;
            //leftside
            caseBordure[xi + 1][yi][0].id = index;
        }
    }

    // horizontal borders
    for (int xi = 0; xi < size; ++xi) {
        for (int yi = 0; yi < size - 1; ++yi) {
            const auto index = borderMaxIndex + (xi * size + yi);
            bordureCases[index].first.x = xi;
            bordureCases[index].first.y = yi;
            bordureCases[index].second.x = xi;
            bordureCases[index].second.y = yi + 1;

            // right side
            caseBordure[xi][yi][3].id = index;
            //leftside
            caseBordure[xi][yi + 1][1].id = index;
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

void BordureCaseConstraint::allow(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth)
{

    // entrypoint : unused : the entrypoint is CasePieceConstraint
    // _first.allow(bordureData, colorData, depth);
    // TODO : minimal importance : all the four borders are denied
    //_second.allow(caseData, pieceData, depth);
}

void BordureCaseConstraint::allow(
    const CaseData &caseData, const PieceData &pieceData, const int &depth)
{
    // entrypoint : unused : the entrypoint is CasePieceConstraint
    //_first.allow(bordureData, colorData, depth);
    // TODO : minimal importance : all the four borders are denied
    //_second.allow(caseData, bordureData, depth);
}

void BordureCaseConstraint::denyOne(
    const CaseData &caseData,
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

void BordureCaseConstraint::denyOne(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    if (bordureData.id == -1) {
        return;
    }

    const auto &caseDataFirst = bordureCases[bordureData.id].first;
    const auto &caseDataSecond = bordureCases[bordureData.id].second;

    // SAVAGE !
    if (bordureData.id < borderMaxIndex) { // vertical
        // TODO : RIGHT = 2;
        for (auto &iterator : colorPieces[colorData.id][2]) {
            _second.denyOne(caseDataFirst, iterator, depth, persistent);
        }
        for (auto &iterator : colorPieces[colorData.id][0]) {
            _second.denyOne(caseDataSecond, iterator, depth, persistent);
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

void BordureCaseConstraint::addOne(
    const CaseData &caseData,
    const PieceData &pieceData,
    const int &depth, const int &persistent)
{
    // entrypoint : the entrypoint is CasePieceConstraint so the oneway is CaPi to BoCo
    for (int rotation = 0; rotation < 4; ++rotation) {
        const auto &bordureData =
            caseBordure[caseData.x][caseData.y][rotation];
        const auto &colorData =
            pieceColors[pieceData.id][pieceData.rotation][rotation];

        _first.addOne(bordureData, colorData, depth, persistent);
    }
}

void BordureCaseConstraint::addOne(
    const BordureData &bordureData,
    const ColorData &colorData,
    const int &depth,
    const int &persistent)
{
    // entrypoint : unused : the entrypoint is CasePieceConstraint, addOne never go up
    /*
    if (bordureData.id == -1) {
        return;
    }

    const auto &caseDataFirst = bordureCases[bordureData.id].first;
    const auto &caseDataSecond = bordureCases[bordureData.id].second;

    // SAVAGE !
    if (bordureData.id < borderMaxIndex) { // vertical
        // TODO : RIGHT = 2;
        for (auto &iterator : colorPieces[colorData.id][2]) {
            _second.addOne(caseDataFirst, iterator, depth, persistent);
        }
        for (auto &iterator : colorPieces[colorData.id][0]) {
            _second.addOne(caseDataSecond, iterator, depth, persistent);
        }
    } else if (bordureData.id >= borderMaxIndex) { // horizontal
        for (auto &iterator : colorPieces[colorData.id][3]) {
            _second.addOne(caseDataFirst, iterator, depth, persistent);
        }
        for (auto &iterator : colorPieces[colorData.id][1]) {
            _second.addOne(caseDataSecond, iterator, depth, persistent);
        }
    }
    */
}

void BordureCaseConstraint::deny(
    const BordureData &bordureData, const int &depth, const int &persistent)
{
    //TODO : minimal importance, certainly not used
    //_second.deny(caseData,depth)
}

void BordureCaseConstraint::deny(
    const CaseData &caseData, const int &depth, const int &persistent)
{
    //TODO : minimal importance, certainly not used
    //_first.deny(bordureData,depth);
}
