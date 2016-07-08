#include "CasePieceSolver.h"

void CasePieceSolver::initialize(PathFinder &pathFinder,
    ConstraintInterface &constraintInterface,
    vector<unique_ptr<ModelInterface>> &models,
    GameImportData &gameImportData)
{
    this->pathFinder = &pathFinder;
    this->pieceCaseConstraint = static_cast<CasePieceConstraint *>(&constraintInterface);
    this->models = &models;
    this->game = &gameImportData;


    // initialisation de mon plateau de verification (sera supprimé lors de l'introduction des couleurs
    // TODO : supprimer avec l'ajout des couleurs
    plateau.resize(game->size,
        vector<vector<int>>(game->size,
            vector<int>(4, -1)));
}

void CasePieceSolver::resolve()
{
    int depth = 0;

    resolve(depth);
}

void CasePieceSolver::resolve(int &depth)
{
    CaseData *caseData = static_cast<CaseData *>(pathFinder->nextVariable(depth));

    if (caseData->valid) {
        resolve(*caseData, depth);
    }

    delete caseData;

    // end of recursivity, rolling back to depth
    for (int model = 0; model < models->size(); ++model) {
        models->operator[](model)->rollback(depth);
    }
}

void CasePieceSolver::resolve(CaseData &caseData, int &depth)
{
    while (pathFinder->hasNextValue(caseData, depth)) {

        PieceData *pieceData = static_cast<PieceData *>(pathFinder->nextValue(caseData));

        if (isPossible(caseData, *pieceData)) {
            putPiece(caseData, *pieceData);
            pieceCaseConstraint->accept(caseData, *pieceData, depth);
            cout << depth << " " << pieceData->id << ":" << pieceData->rotation << endl;
            ++depth;
            resolve(depth);
            --depth;
            // end of recursivity, rolling back to the beginning of the current depth
            // TODO : fine tune this thing
            for (int model = 0; model < models->size(); ++model) {
                models->operator[](model)->rollback(depth);
            }
            popPiece(caseData, *pieceData);
        }
        pieceCaseConstraint->discard(caseData, *pieceData, depth);
        delete pieceData;
    }
}

bool CasePieceSolver::isPossible(CaseData &data, PieceData &pieceData)
{
    if (data.x == 0) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][1] != 0) {
            return false;
        }
    } else if (data.x == game->size - 1) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][3] != 0) {
            return false;
        }
    } else if ((plateau[data.x - 1][data.y][3] != -1
        && game->pieces[pieceData.id]->colors[pieceData.rotation][1] != plateau[data.x - 1][data.y][3]) ||
        (plateau[data.x + 1][data.y][1] != -1
            && game->pieces[pieceData.id]->colors[pieceData.rotation][3] != plateau[data.x + 1][data.y][1]) ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][3] == 0 ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][1] == 0) {
        return false;
    }

    if (data.y == 0) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][0] != 0) {
            return false;
        }
    } else if (data.y == game->size - 1) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][2] != 0) {
            return false;
        }
    } else if (plateau[data.x][data.y - 1][2] != -1
        && game->pieces[pieceData.id]->colors[pieceData.rotation][0] != plateau[data.x][data.y - 1][2] ||
        plateau[data.x][data.y + 1][0] != -1
            && game->pieces[pieceData.id]->colors[pieceData.rotation][2] != plateau[data.x][data.y + 1][0] ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][2] == 0 ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][0] == 0) {
        return false;
    }

    return true;
}

void CasePieceSolver::putPiece(CaseData &data, PieceData &pieceData)
{
    plateau[data.x][data.y] = game->pieces[pieceData.id]->colors[pieceData.rotation];
}

void CasePieceSolver::popPiece(CaseData &data, PieceData &pieceData)
{
    for (int i = 0; i < 4; ++i) {
        plateau[data.x][data.y][i] = -1;
    }
}
