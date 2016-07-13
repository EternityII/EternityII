#include "CasePieceSolver.h"

CasePieceSolver::CasePieceSolver(PathFinder &pathFinder,
    ConstraintInterface &constraintInterface,
    vector<unique_ptr<ModelInterface>> &models,
    GameImportData &gameImportData)
    : SolverInterface(pathFinder, models, gameImportData)
{
    this->_constraint =
        static_cast<CasePieceConstraint *>(&constraintInterface);

    // initialisation de mon plateau de verification (sera supprimé lors de l'introduction des couleurs
    // TODO : supprimer avec l'ajout des couleurs
    plateau.resize(game->size,
        vector<PieceData>(game->size, PieceData(-1, 0)));
}

void CasePieceSolver::resolve()
{
    int depth = 0;
    // placing the first piece to avoid rotation duplication
    CaseData
        *caseData = static_cast<CaseData *>(pathFinder->nextVariable(depth));
    pathFinder->hasNextValue(*caseData, depth);
    PieceData
        *pieceData = static_cast<PieceData *>(pathFinder->nextValue(*caseData));
    putPiece(*caseData, *pieceData);
    _constraint->accept(*caseData, *pieceData, depth);

    cout << depth << " " << pieceData->id << ":" << pieceData->rotation << endl;

    ++depth;

    clock_t start = clock();

    resolve(depth);

    cout << "temps " << (clock() - start) / (double)
        (CLOCKS_PER_SEC) << endl;

    delete caseData;
    delete pieceData;
}

void CasePieceSolver::resolve(int &depth)
{
    CaseData
        *caseData = static_cast<CaseData *>(pathFinder->nextVariable(depth));

    if (caseData->valid) {
        resolve(*caseData, depth);
    }

    delete caseData;

}

void CasePieceSolver::resolve(CaseData &caseData, int &depth)
{
    while (pathFinder->hasNextValue(caseData, depth)) {

        PieceData *pieceData =
            static_cast<PieceData *>(pathFinder->nextValue(caseData));

        if (isPossible(caseData, *pieceData)) {
            putPiece(caseData, *pieceData);
            _constraint->accept(caseData, *pieceData, depth);

            cout << depth << " " << pieceData->id << ":" << pieceData->rotation
                << endl;

            ++depth;
            resolve(depth);
            --depth;
            // partial backtracking, up to discarded tuples
            for (int model = 0; model < models->size(); ++model) {
                models->operator[](model)->rollback(depth, false);
            }
            popPiece(caseData, *pieceData);
        }
        _constraint->discard(caseData, *pieceData, depth);
        delete pieceData;
    }

    // end of recursivity, rolling back to the beginning of depth
    for (int model = 0; model < models->size(); ++model) {
        models->operator[](model)->rollback(depth);
    }

}

bool CasePieceSolver::isPossible(CaseData &caseData, PieceData &pieceData)
{
    if (caseData.x == 0) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][0] != 0 ||
            isBorderFalse(caseData, pieceData, 2)) {
            return false;
        }
    } else if (caseData.x == game->size - 1) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][2] != 0 ||
            isBorderFalse(caseData, pieceData, 0)) {
            return false;
        }
    } else if (game->pieces[pieceData.id]->colors[pieceData.rotation][0] == 0 ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][2] == 0 ||
        isBorderFalse(caseData, pieceData, 0) ||
        isBorderFalse(caseData, pieceData, 2)) {
        return false;
    }

    if (caseData.y == 0) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][1] != 0 ||
            isBorderFalse(caseData, pieceData, 3)) {
            return false;
        }
    } else if (caseData.y == game->size - 1) {
        if (game->pieces[pieceData.id]->colors[pieceData.rotation][3] != 0 ||
            isBorderFalse(caseData, pieceData, 1)) {
            return false;
        }
    } else if (game->pieces[pieceData.id]->colors[pieceData.rotation][1] == 0 ||
        game->pieces[pieceData.id]->colors[pieceData.rotation][3] == 0 ||
        isBorderFalse(caseData, pieceData, 1) ||
        isBorderFalse(caseData, pieceData, 3)) {
        return false;
    }

    return true;
}

bool CasePieceSolver::isBorderFalse
    (const CaseData &caseData, const PieceData &pieceData, const int border)
const
{
    if (border == 0) {
        return plateau[caseData.x - 1][caseData.y].id != -1 &&
            game->pieces[pieceData.id]->colors[pieceData.rotation][0] !=
                game->pieces[plateau[caseData.x - 1][caseData.y].id]
                    ->colors[plateau[caseData.x - 1][caseData.y].rotation][2];
    } else if (border == 1) {
        return plateau[caseData.x][caseData.y - 1].id != -1 &&
            game->pieces[pieceData.id]->colors[pieceData.rotation][1] !=
                game->pieces[plateau[caseData.x][caseData.y - 1].id]
                    ->colors[plateau[caseData.x][caseData.y - 1].rotation][3];
    } else if (border == 2) {
        return plateau[caseData.x + 1][caseData.y].id != -1 &&
            game->pieces[pieceData.id]->colors[pieceData.rotation][2] !=
                game->pieces[plateau[caseData.x + 1][caseData.y].id]
                    ->colors[plateau[caseData.x + 1][caseData.y].rotation][0];
    } else if (border == 3) {
        return plateau[caseData.x][caseData.y + 1].id != -1 &&
            game->pieces[pieceData.id]->colors[pieceData.rotation][3] !=
                game->pieces[plateau[caseData.x][caseData.y + 1].id]
                    ->colors[plateau[caseData.x][caseData.y + 1].rotation][1];
    }
}

void CasePieceSolver::putPiece(CaseData &caseData, PieceData &pieceData)
{
    plateau[caseData.x][caseData.y].id = pieceData.id;
    plateau[caseData.x][caseData.y].rotation = pieceData.rotation;
}
void CasePieceSolver::popPiece(CaseData &caseData, PieceData &pieceData)
{
    plateau[caseData.x][caseData.y].id = -1;
}
