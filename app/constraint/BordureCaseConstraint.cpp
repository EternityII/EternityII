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
    // TODO : ambigu :/

    // todo : bordurecases , caseBordure, colorPieces, pieceColors
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
