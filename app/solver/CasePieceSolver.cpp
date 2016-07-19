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

    maxDepth = game->size * game->size;
}

void CasePieceSolver::resolve()
{
    int depth = 0;
    // placing the first piece to avoid rotation duplication
    CaseData *caseData = new CaseData(0, 0);
    PieceData *pieceData = new PieceData(0, 0);
    putPiece(*caseData, *pieceData);
    _constraint->accept(*caseData, *pieceData, depth);
    ++quantityVariables;
    ++quantityNodes;

    cout << depth << " " << pieceData->id << ":" << pieceData->rotation << endl;

    ++depth;

    clock_t start = clock();

    resolve(depth);

    cout << "Timers :"
        << "\n- variable : " << durationVariable / (double) CLOCKS_PER_SEC
        << "s\n- value : " << durationValue / (double) CLOCKS_PER_SEC
        << "s\n- accepting : " << durationAccept / (double) CLOCKS_PER_SEC
        << "s\n- discarding : " << durationDiscard / (double) CLOCKS_PER_SEC
        << "s\n- partial rollback  : "
        << durationPartialRollback / (double) CLOCKS_PER_SEC
        << "s\n- rollback  : " << durationRollback / (double) CLOCKS_PER_SEC
        << "s\n- solving time : " << (clock() - start) / (double) CLOCKS_PER_SEC
        << "s\nNodes :"
        << "\n- Total : " << quantityNodes
        << "\n- First Solution : " << quantityNodesFirstSolution
        << "\nSolutions : " << quantitySolutions
        << "\nCounters : "
        << "\n- Variable : " << quantityVariables
        << "\n- Value : " << quantityValues << endl;

    delete caseData;
    delete pieceData;
}

void CasePieceSolver::resolve(int &depth)
{
    if (depth == maxDepth) {
        if (quantitySolutions == 0) {
            quantityNodesFirstSolution = quantityNodes;
        }
        ++quantitySolutions;
    }
    // chronos
    clock_t beginVarDuration = clock();
    if (pathFinder->hasNextVariable(depth)) {
        ++quantityNodes;
        ++quantityVariables;
        CaseData *caseData =
            static_cast<CaseData *>(pathFinder->nextVariable(depth));
        durationVariable += clock() - beginVarDuration;

        cout << depth << " " << caseData->x << "," << caseData->y;

        // need to choose value now !
        resolve(*caseData, depth);

        delete caseData;
    }

}

void CasePieceSolver::resolve(CaseData &caseData, int &depth)
{
    clock_t beginVal = clock();
    while (pathFinder->hasNextValue(caseData, depth)) {
        PieceData *pieceData =
            static_cast<PieceData *>(pathFinder->nextValue(caseData));
        durationValue += clock() - beginVal;
        ++quantityValues;

        if (isPossible(caseData, *pieceData)) {
            putPiece(caseData, *pieceData);

            // accept value&variable
            clock_t beginAccept = clock();
            _constraint->accept(caseData, *pieceData, depth);
            durationAccept += clock() - beginAccept;

            // DEBUG :
            cout << " " << pieceData->id << ":" << pieceData->rotation << endl;

            /*************/
            /* RECURSION */
            /*************/
            ++depth;
            resolve(depth);
            --depth;
            /*****************/
            /* END RECURSION */
            /*****************/

            // partial backtracking
            clock_t beginPartialRollback = clock();
            for (int model = 0; model < models->size(); ++model) {
                models->operator[](model)->rollback(depth, false);
            }
            durationPartialRollback += clock() - beginPartialRollback;

            popPiece(caseData, *pieceData);
        }

        // discarding value&variable
        clock_t beginDiscard = clock();
        _constraint->discard(caseData, *pieceData, depth);
        durationDiscard += clock() - beginDiscard;

        delete pieceData;

        beginVal = clock();
    }

    // end of recursivity, rolling back to the beginning of depth
    clock_t beginRollback = clock();
    for (int model = 0; model < models->size(); ++model) {
        models->operator[](model)->rollback(depth);
    }
    durationRollback += clock() - beginRollback;

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
