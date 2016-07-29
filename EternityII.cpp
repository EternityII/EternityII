#include "EternityII.h"
#include "app/model/PieceModel.h"
#include "app/model/CaseModel.h"
#include "app/constraint/CasePieceConstraint.h"
#include "app/solver/CasePieceSolver.h"
#include "app/pathfinder/variable/CaseOptimistVariable.h"
#include "app/pathfinder/variable/CaseRowscanVariable.h"
#include "app/pathfinder/variable/CaseDiagonalVariable.h"
#include "app/pathfinder/variable/CasePessimistVariable.h"
#include "app/pathfinder/value/PieceNormalValue.h"
#include "app/pathfinder/value/PieceOptimistValue.h"
#include "app/pathfinder/value/PiecePessimistValue.h"
#include "app/model/BordureModel.h"
#include "app/model/ColorModel.h"
#include "app/constraint/BordureCaseConstraint.h"
#include "app/constraint/BordureColorConstraint.h"
#include "app/constraint/ColorPieceConstraint.h"


void EternityII::bootstrap(string &filename, int &variable, int &value)
{
    // opening the file
    IO io(filename, ios::in);

    // GameData
    gameImport = make_unique<GameImportData>();

    // importing gameData from the file
    import(io);

    /* ======================== */
    /* SETTING UP THE FRAMEWORK */
    /* ======================== */

    //Event Manager
    eventManager = make_unique<EventManager>();

    // Models
    auto pieceModel = make_unique<PieceModel>(*gameImport, *eventManager);
    auto caseModel = make_unique<CaseModel>(*gameImport, *eventManager);
    auto bordureModel = make_unique<BordureModel>(*gameImport, *eventManager);
    auto colorModel = make_unique<ColorModel>(*gameImport, *eventManager);

    // Constraints
    auto casePieceConstraint = make_unique<CasePieceConstraint>(
        *caseModel, *pieceModel, *eventManager);

    auto bordureColorConstraint = make_unique<BordureColorConstraint>(
        *bordureModel, *colorModel, *eventManager);

    auto bordureCaseConstraint = make_unique<BordureCaseConstraint>(
        *bordureModel, *caseModel, *eventManager, *gameImport);

    auto colorPieceConstraint = make_unique<ColorPieceConstraint>(
        *colorModel, *pieceModel, *eventManager, *gameImport);


    // Variable
    unique_ptr<VariableInterface> variableInterface;
    switch (variable) {
        case 1: /* CaseDiagonalVariable */
            variableInterface = make_unique<CaseDiagonalVariable>(*caseModel);
            break;
        case 2: /* CaseOptimistVariable */
            variableInterface = make_unique<CaseOptimistVariable>(*caseModel);
            break;
        case 3: /* CasePessimistVariable */
            variableInterface = make_unique<CasePessimistVariable>(*caseModel);
            break;
        case 0: /* CaseRowscanVariable */
        default:
            variableInterface = make_unique<CaseRowscanVariable>(*caseModel);
    }

    // Value
    unique_ptr<ValueInterface> valueInterface;
    switch (value) {
        case 1: /* PieceOptimistValue */
            valueInterface = make_unique<PieceOptimistValue>(*pieceModel);
            break;
        case 2: /* PiecePessimistValue */
            valueInterface = make_unique<PiecePessimistValue>(*pieceModel);
            break;
        case 0: /* PieceNormalValue */
        default:
            valueInterface = make_unique<PieceNormalValue>(*pieceModel);
    }

    // PathFinder
    pathFinder =
        make_unique<PathFinder>(move(variableInterface), move(valueInterface));

    // Solver
    solver = make_unique<CasePieceSolver>(
        *pathFinder, *casePieceConstraint, models, *gameImport
    );

    /* ============================== */
    /* STORING CONSTRAINTS AND MODELS */
    /* ============================== */
    constraints.push_back(move(casePieceConstraint)); // 0
    constraints.push_back(move(bordureColorConstraint)); // 1
    constraints.push_back(move(bordureCaseConstraint)); // 2
    constraints.push_back(move(colorPieceConstraint)); // 3

    models.push_back(move(pieceModel));
    models.push_back(move(caseModel));
    models.push_back(move(bordureModel));
    models.push_back(move(colorModel));

    /* ======================== */
    /* LAUNCHING THE RESOLUTION */
    /* ======================== */
    solver->resolve();
}

void EternityII::import(IO &io)
{
    int currentNumber;
    int placedPieces;

    // taille du jeu
    io >> currentNumber;
    gameImport->setSize(currentNumber);

    // Number of colors
    io >> gameImport->colorsQte;

    ++gameImport->colorsQte;

    gameImport->colorCount.resize(gameImport->colorsQte, 0);

    // pre-placed pieces
    io >> placedPieces;

    for (int i = 0; i < placedPieces; ++i) {
        for (int j = 0; j < 4; ++j) {
            // We don't need to know the preplaced pieces // yet
            io >> currentNumber;
        }
    }

    for (int id = 0; id < gameImport->depth; ++id) {
        // importing the pieces
        unique_ptr<PieceImportData> piece = make_unique<PieceImportData>();
        // the zero defines the type of the piece
        int zeroCount = 0;


        for (int i = 0; i < 4; ++i) {
            io >> currentNumber;
            // DEBUG :
            // cout << currentNumber << " ";

            if (currentNumber == 0) {
                ++zeroCount;
            }

            piece->colors[0][i] = currentNumber;
            ++gameImport->colorCount[piece->colors[0][i]];
        }

        // duplicating the colors to 4 possible rotations
        for (int i = 0; i < 4; ++i) {
            for (int j = 1; j <= 3; ++j) {
                piece->colors[j][(j + i) % 4] = piece->colors[0][i];
            }
        }

        piece->id = id;
        piece->type = zeroCount;
        // DEBUG :
        // cout << endl;

        // moving the piece into the game wrapper
        gameImport->pieces[id] = move(piece);
    }
}
