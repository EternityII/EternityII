#include "EternityII.h"
#include "app/model/PieceModel.h"
#include "app/model/CaseModel.h"
#include "app/constraint/CasePieceConstraint.h"
#include "app/pathfinder/variable/CaseRowscanVariable.h"
#include "app/pathfinder/value/PieceNormalValue.h"
#include "app/solver/CasePieceSolver.h"


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
    unique_ptr<PieceModel>
        pieceModel = make_unique<PieceModel>(*gameImport, *eventManager);
    unique_ptr<CaseModel>
        caseModel = make_unique<CaseModel>(*gameImport, *eventManager);

    // Constraints
    unique_ptr<CasePieceConstraint>
        casePieceConstraint = make_unique<CasePieceConstraint>(*caseModel,
        *pieceModel,
        *eventManager);

    // Variable Value
    unique_ptr<VariableInterface>
        variableInterface = make_unique<CaseRowscanVariable>(*caseModel);
    unique_ptr<ValueInterface>
        valueInterface = make_unique<PieceNormalValue>(*pieceModel);

    // PathFinder
    pathFinder =
        make_unique<PathFinder>(move(variableInterface), move(valueInterface));

    // Solver
    solver = make_unique<CasePieceSolver>(*pathFinder,
        *casePieceConstraint,
        models,
        *gameImport);

    /* ============================== */
    /* STORING CONSTRAINTS AND MODELS */
    /* ============================== */
    constraints.push_back(move(casePieceConstraint));

    models.push_back(move(pieceModel));
    models.push_back(move(caseModel));

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
    io >> currentNumber;

    // pre-placed pieces
    io >> placedPieces;

    for (int i = 0; i < placedPieces; i++) {
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
