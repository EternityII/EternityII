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

    borderMaxIndex = gameImportData.size * (gameImportData.size - 1);


    /* 
     * Initialisation
     */

    bordureCases.resize(2 * borderMaxIndex);

    caseBordure.resize(gameImportData.size, // x
        vector<vector<BordureData> >(gameImportData.size, // y
            vector<BordureData>(4, BordureData(-1)))); // border n°

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


    for (int pieceId = 0; pieceId < gameImportData.piecesQte; ++pieceId) {
        for (int rotation = 0; rotation < 4; ++rotation) {
            for (int face = 0; face < 4; ++face) {
                colorPieces[gameImportData.pieces[pieceId]
                    ->colors[rotation][face]][face]
                    .emplace_back(pieceId, rotation);

                pieceColors[pieceId][rotation][face].id =
                    gameImportData.pieces[pieceId]->colors[rotation][face];
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
