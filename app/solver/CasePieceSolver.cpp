#include "CasePieceSolver.h"

CasePieceSolver::CasePieceSolver(PathFinder &pathFinder,
    ConstraintInterface &constraintInterface,
    vector<unique_ptr<ModelInterface>> &models,
    GameImportData &gameImportData)
    : SolverInterface(pathFinder, models, gameImportData)
{
    this->_constraintInterface = static_cast<CasePieceConstraint *>(&constraintInterface);

    // initialisation de mon plateau de verification (sera supprimé lors de l'introduction des couleurs
    // TODO : supprimer avec l'ajout des couleurs
    plateau.resize(game->size,
        vector<PieceData>(game->size));
}

void CasePieceSolver::resolve()
{
    int depth = 0;
    // placing the first piece to avoid rotation duplication
    CaseData *caseData = static_cast<CaseData *>(pathFinder->nextVariable(depth));
    pathFinder->hasNextValue(*caseData, depth);
    PieceData *pieceData = static_cast<PieceData *>(pathFinder->nextValue(*caseData));
    putPiece(*caseData, *pieceData);
    _constraintInterface->accept(*caseData, *pieceData, depth);
    cout << depth << " " << pieceData->id << ":" << pieceData->rotation << endl;
    ++depth;

    resolve(depth);

    delete caseData;
    delete pieceData;
}

void CasePieceSolver::resolve(int &depth)
{
    CaseData *caseData = static_cast<CaseData *>(pathFinder->nextVariable(depth));

    if (caseData->valid) {
        resolve(*caseData, depth);
    }

    delete caseData;

}

void CasePieceSolver::resolve(CaseData &caseData, int &depth)
{
    while (pathFinder->hasNextValue(caseData, depth)) {

        PieceData *pieceData = static_cast<PieceData *>(pathFinder->nextValue(caseData));

        if (isPossible(caseData, *pieceData)) {
            putPiece(caseData, *pieceData);
            _constraintInterface->accept(caseData, *pieceData, depth);

            //cout << depth << " " << pieceData->id << ":" << pieceData->rotation << endl;

            ++depth;
            resolve(depth);
            --depth;
            // partial backtracking, up to discarded tuples
            for (int model = 0; model < models->size(); ++model) {
                models->operator[](model)->rollbackPartial(depth);
            }
            popPiece(caseData, *pieceData);
        }
        _constraintInterface->discard(caseData, *pieceData, depth);
        delete pieceData;
    }

    // end of recursivity, rolling back to the beginning of depth
    for (int model = 0; model < models->size(); ++model) {
        models->operator[](model)->rollback(depth);
    }

}

bool CasePieceSolver::isPossible(CaseData &data, PieceData &pieceData)
{/*
    if (data.x == 0) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][0] != 0 ||
            (game->pieces[pieceData.id]->colors[pieceData.rotation][2] != plateau[data.x + 1][data.y][0]
                && plateau[data.x + 1][data.y][0] != -1)) {
            return false;
        }
    } else if (data.x == game->size - 1) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][2] != 0 ||
            (game->pieces[pieceData.id]->colors[pieceData.rotation][0] != plateau[data.x - 1][data.y][2]
                && plateau[data.x - 1][data.y][2] != -1)) {
            return false;
        }
    } else if ((plateau[data.x - 1][data.y][2] != -1
        && game->pieces[pieceData.id]->colors[pieceData.rotation][0] != plateau[data.x - 1][data.y][2]) ||
        (plateau[data.x + 1][data.y][0] != -1
            && game->pieces[pieceData.id]->colors[pieceData.rotation][2] != plateau[data.x + 1][data.y][0]) ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][2] == 0 ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][0] == 0) {
        return false;
    }

    if (data.y == 0) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][1] != 0 ||
            (game->pieces[pieceData.id]->colors[pieceData.rotation][3] != plateau[data.x][data.y + 1][1]
                && plateau[data.x][data.y + 1][1] != -1)) {
            return false;
        }
    } else if (data.y == game->size - 1) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][3] != 0 ||
            (game->pieces[pieceData.id]->colors[pieceData.rotation][1] != plateau[data.x][data.y - 1][3]
                && plateau[data.x][data.y - 1][3] != -1)) {
            return false;
        }
    } else if (plateau[data.x][data.y - 1][3] != -1
        && game->pieces[pieceData.id]->colors[pieceData.rotation][1] != plateau[data.x][data.y - 1][3] ||
        plateau[data.x][data.y + 1][1] != -1
            && game->pieces[pieceData.id]->colors[pieceData.rotation][3] != plateau[data.x][data.y + 1][1] ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][3] == 0 ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][1] == 0) {
        return false;
    }
*/
    return true;
}

void CasePieceSolver::putPiece(CaseData &data, PieceData &pieceData)
{
    plateau[data.x][data.y].id = pieceData.id;
    plateau[data.x][data.y].rotation = pieceData.rotation;
}
void CasePieceSolver::popPiece(CaseData &data, PieceData &pieceData)
{
    for (int i = 0; i < 4; ++i) {
        plateau[data.x][data.y].id = -1;
    }
}
