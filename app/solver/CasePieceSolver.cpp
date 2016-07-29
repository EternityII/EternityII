#include "CasePieceSolver.h"

CasePieceSolver::CasePieceSolver(PathFinder &pathFinder,
    ConstraintInterface &constraintInterface,
    vector<unique_ptr<ModelInterface>> &models,
    GameImportData &gameImportData)
    : SolverInterface(pathFinder, models, gameImportData),
      _constraint(static_cast<CasePieceConstraint &>(constraintInterface))
{
    // initialisation de mon plateau de verification (sera supprimé lors de l'introduction des couleurs
    // TODO : supprimer avec l'ajout des couleurs

    size = game.size;
    plateau.resize(size,
        vector<PieceData>(size, PieceData(-1, 0)));


    maxDepth = game.depth;
    quantityNodesByDepth.resize(maxDepth, 0);

    firstOpti();
}

void CasePieceSolver::resolve()
{
    int depth = 0;
    // placing the first piece to avoid rotation duplication
    CaseData *caseData = new CaseData(0, 0);
    PieceData *pieceData = new PieceData(0, 0);
    putPiece(*caseData, *pieceData);
    _constraint.allow(*caseData, *pieceData, depth);
    ++quantityVariables;
    ++quantityNodes;

    // DEBUG :
    //cout << depth << " " << pieceData->id << ":" << pieceData->rotation << endl;

    ++depth;

    clock_t start = clock();

    resolve(depth);

    cout << "Timers :"
         << "\n- variable : " << durationVariable / (double) CLOCKS_PER_SEC
         << "s\n- value : " << durationValue / (double) CLOCKS_PER_SEC
         << "s\n- allowing : " << durationAllow / (double) CLOCKS_PER_SEC
         << "s\n- denying : " << durationDeny / (double) CLOCKS_PER_SEC
         << "s\n- partial rollback  : "
         << durationPartialRollback / (double) CLOCKS_PER_SEC
         << "s\n- rollback  : " << durationRollback / (double) CLOCKS_PER_SEC
         << "s\n- solving time : "
         << (clock() - start) / (double) CLOCKS_PER_SEC
         << "s\nNodes :"
         << "\n- Total : " << quantityNodes
         << "\n- First Solution : " << quantityNodesFirstSolution
         << "\n- By Depth : " << endl;

    for (const auto &item : quantityNodesByDepth) {
        if (item == 0) {
            cout << 0;
        } else {
            cout << (item / (long double) quantityNodes) * 100;

        }
        cout << "%" << endl;
    }

    cout << "\nSolutions : " << quantitySolutions
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
    if (pathFinder.hasNextVariable(depth)) {
        ++quantityNodes;
        ++quantityNodesByDepth[depth];
        ++quantityVariables;
        CaseData *caseData =
            static_cast<CaseData *>(pathFinder.nextVariable(depth));
        durationVariable += clock() - beginVarDuration;

        //DEBUG :
        //cout << depth << " " << caseData->x << "," << caseData->y;

        // need to choose value now !
        resolve(*caseData, depth);

        delete caseData;
    }

}

void CasePieceSolver::resolve(CaseData &caseData, int &depth)
{
    clock_t beginVal = clock();
    while (pathFinder.hasNextValue(caseData, depth)) {
        PieceData *pieceData =
            static_cast<PieceData *>(pathFinder.nextValue(caseData));
        durationValue += clock() - beginVal;
        ++quantityValues;

        if (isPossible(caseData, *pieceData)) {
            putPiece(caseData, *pieceData);

            // allow value&variable
            clock_t beginAllow = clock();
            _constraint.allow(caseData, *pieceData, depth);
            durationAllow += clock() - beginAllow;

            // DEBUG :
            //cout << " " << pieceData->id << ":" << pieceData->rotation << endl;

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
            for (auto &iter : models) {
                iter->rollback(depth, false);
            }
            durationPartialRollback += clock() - beginPartialRollback;

            popPiece(caseData, *pieceData);
        }

        // denying value&variable
        clock_t beginDeny = clock();
        _constraint.denyOne(caseData, *pieceData, depth, 0);
        durationDeny += clock() - beginDeny;

        delete pieceData;

        beginVal = clock();
    }

    // end of recursivity, rolling back to the beginning of depth
    clock_t beginRollback = clock();
    for (auto &iter : models) {
        iter->rollback(depth);
    }
    durationRollback += clock() - beginRollback;

}

bool CasePieceSolver::isPossible(
    const CaseData &caseData, const PieceData &pieceData) const
{
    if (caseData.x == 0) {
        if (game.pieces[pieceData.id]->colors[pieceData.rotation][0] != 0 or
            isBorderFalse(caseData, pieceData, 2)) {
            return false;
        }
    } else if (caseData.x == game.size - 1) {
        if (game.pieces[pieceData.id]->colors[pieceData.rotation][2] != 0 or
            isBorderFalse(caseData, pieceData, 0)) {
            return false;
        }
    } else if (game.pieces[pieceData.id]->colors[pieceData.rotation][0] == 0 or
        game.pieces[pieceData.id]->colors[pieceData.rotation][2] == 0 or
        isBorderFalse(caseData, pieceData, 0) or
        isBorderFalse(caseData, pieceData, 2)) {
        return false;
    }

    if (caseData.y == 0) {
        if (game.pieces[pieceData.id]->colors[pieceData.rotation][1] != 0 or
            isBorderFalse(caseData, pieceData, 3)) {
            return false;
        }
    } else if (caseData.y == game.size - 1) {
        if (game.pieces[pieceData.id]->colors[pieceData.rotation][3] != 0 or
            isBorderFalse(caseData, pieceData, 1)) {
            return false;
        }
    } else if (game.pieces[pieceData.id]->colors[pieceData.rotation][1] == 0 or
        game.pieces[pieceData.id]->colors[pieceData.rotation][3] == 0 or
        isBorderFalse(caseData, pieceData, 1) or
        isBorderFalse(caseData, pieceData, 3)) {
        return false;
    }

    return true;
}

bool CasePieceSolver::isBorderFalse(
    const CaseData &caseData,
    const PieceData &pieceData,
    const int border) const
{
    if (border == 0) {
        return plateau[caseData.x - 1][caseData.y].id != -1 and
            game.pieces[pieceData.id]->colors[pieceData.rotation][0] !=
                game.pieces[plateau[caseData.x - 1][caseData.y].id]
                    ->colors[plateau[caseData.x - 1][caseData.y].rotation][2];
    } else if (border == 1) {
        return plateau[caseData.x][caseData.y - 1].id != -1 and
            game.pieces[pieceData.id]->colors[pieceData.rotation][1] !=
                game.pieces[plateau[caseData.x][caseData.y - 1].id]
                    ->colors[plateau[caseData.x][caseData.y - 1].rotation][3];
    } else if (border == 2) {
        return plateau[caseData.x + 1][caseData.y].id != -1 and
            game.pieces[pieceData.id]->colors[pieceData.rotation][2] !=
                game.pieces[plateau[caseData.x + 1][caseData.y].id]
                    ->colors[plateau[caseData.x + 1][caseData.y].rotation][0];
    } else if (border == 3) {
        return plateau[caseData.x][caseData.y + 1].id != -1 and
            game.pieces[pieceData.id]->colors[pieceData.rotation][3] !=
                game.pieces[plateau[caseData.x][caseData.y + 1].id]
                    ->colors[plateau[caseData.x][caseData.y + 1].rotation][1];
    }
}

void CasePieceSolver::putPiece(
    const CaseData &caseData, const PieceData &pieceData)
{
    plateau[caseData.x][caseData.y] = pieceData;
}
void CasePieceSolver::popPiece(
    const CaseData &caseData, const PieceData &pieceData)
{
    plateau[caseData.x][caseData.y].id = -1;
}

void CasePieceSolver::firstOpti()
{
    // because entry point u know
    for (int variable = 1; variable < size - 1; ++variable) {
        CaseData caseXBeginEdge(0, variable);
        CaseData caseXEndEdge(size - 1, variable);
        CaseData caseYBeginEdge(variable, 0);
        CaseData caseYEndEdge(variable, size - 1);

        // interior piece cannot be put on a edge case
        for (int nInsidePiece = (size - 1) * 4;
             nInsidePiece < maxDepth;
             ++nInsidePiece) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                PieceData pieceData(nInsidePiece, rotation);

                _constraint.denyOne(caseXBeginEdge, pieceData, 0, 0);
                _constraint.denyOne(caseXEndEdge, pieceData, 0, 0);
                _constraint.denyOne(caseYBeginEdge, pieceData, 0, 0);
                _constraint.denyOne(caseYEndEdge, pieceData, 0, 0);
            }

        }

        // Edge pieces can be put only at a specific rotation on the edge
        for (int nBordPiece = 4; nBordPiece < (size - 1) * 4;
             ++nBordPiece) {
            PieceData pieceEdgeLeft(nBordPiece, 0);
            PieceData pieceEdgeTop(nBordPiece, 1);
            PieceData pieceEdgeRight(nBordPiece, 2);
            PieceData pieceEdgeBottom(nBordPiece, 3);

            _constraint.denyOne(caseXBeginEdge, pieceEdgeTop, 0, 0);
            _constraint.denyOne(caseXBeginEdge, pieceEdgeRight, 0, 0);
            _constraint.denyOne(caseXBeginEdge, pieceEdgeBottom, 0, 0);

            _constraint.denyOne(caseYBeginEdge, pieceEdgeLeft, 0, 0);
            _constraint.denyOne(caseYBeginEdge, pieceEdgeRight, 0, 0);
            _constraint.denyOne(caseYBeginEdge, pieceEdgeBottom, 0, 0);

            _constraint.denyOne(caseXEndEdge, pieceEdgeLeft, 0, 0);
            _constraint.denyOne(caseXEndEdge, pieceEdgeTop, 0, 0);
            _constraint.denyOne(caseXEndEdge, pieceEdgeBottom, 0, 0);

            _constraint.denyOne(caseYEndEdge, pieceEdgeRight, 0, 0);
            _constraint.denyOne(caseYEndEdge, pieceEdgeTop, 0, 0);
            _constraint.denyOne(caseYEndEdge, pieceEdgeLeft, 0, 0);
        }

        // corner piece cannot be put on edge
        for (int nCornerPiece = 0; nCornerPiece < 4; ++nCornerPiece) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                PieceData cornerPiece(nCornerPiece, rotation);

                _constraint.denyOne(caseXBeginEdge, cornerPiece, 0, 0);
                _constraint.denyOne(caseXEndEdge, cornerPiece, 0, 0);
                _constraint.denyOne(caseYBeginEdge, cornerPiece, 0, 0);
                _constraint.denyOne(caseYEndEdge, cornerPiece, 0, 0);
            }
        }
    }

    // Corner and Edge pieces cannot be put on an interior case
    for (int x = 1; x < size - 1; ++x) {
        for (int y = 1; y < size - 1; ++y) {
            CaseData caseInterieur(x, y);
            for (int nPiece = 0; nPiece < (size - 1) * 4; ++nPiece) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    PieceData pieceData(nPiece, rotation);
                    _constraint.denyOne(caseInterieur, pieceData, 0, 0);
                }
            }
        }
    }

    CaseData caseCornerLeftTop(0, 0);
    CaseData caseCornerTopRight(size - 1, 0);
    CaseData caseCornerRightBot(size - 1, size - 1);
    CaseData caseCornerBotLeft(0, size - 1);

    for (int nPiece = 4; nPiece < maxDepth; ++nPiece) {
        for (int rotation = 0; rotation < 4; ++rotation) {
            PieceData pieceData(nPiece, rotation);

            _constraint.denyOne(caseCornerLeftTop, pieceData, 0, 0);
            _constraint.denyOne(caseCornerTopRight, pieceData, 0, 0);
            _constraint.denyOne(caseCornerRightBot, pieceData, 0, 0);
            _constraint.denyOne(caseCornerBotLeft, pieceData, 0, 0);

        }
    }

    for (int nPieceCorner = 0; nPieceCorner < 4; ++nPieceCorner) {
        PieceData pieceCornerLeftTop(nPieceCorner, 0);
        _constraint.denyOne(caseCornerTopRight, pieceCornerLeftTop, 0, 0);
        _constraint.denyOne(caseCornerRightBot, pieceCornerLeftTop, 0, 0);
        _constraint.denyOne(caseCornerBotLeft, pieceCornerLeftTop, 0, 0);

        PieceData pieceCornerTopRight(nPieceCorner, 1);
        _constraint.denyOne(caseCornerLeftTop, pieceCornerTopRight, 0, 0);
        _constraint.denyOne(caseCornerRightBot, pieceCornerTopRight, 0, 0);
        _constraint.denyOne(caseCornerBotLeft, pieceCornerTopRight, 0, 0);

        PieceData pieceCornerRightBot(nPieceCorner, 2);
        _constraint.denyOne(caseCornerLeftTop, pieceCornerRightBot, 0, 0);
        _constraint.denyOne(caseCornerTopRight, pieceCornerRightBot, 0, 0);
        _constraint.denyOne(caseCornerBotLeft, pieceCornerRightBot, 0, 0);

        PieceData pieceCornerBotLeft(nPieceCorner, 3);
        _constraint.denyOne(caseCornerLeftTop, pieceCornerBotLeft, 0, 0);
        _constraint.denyOne(caseCornerTopRight, pieceCornerBotLeft, 0, 0);
        _constraint.denyOne(caseCornerRightBot, pieceCornerBotLeft, 0, 0);
    }
}