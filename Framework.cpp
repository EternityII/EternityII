#include "Framework.h"

void Framework::bootstrap(string &filename, int &variable, int &value)
{
    IO io(filename, ios::in);

    game = make_unique<GameImportData>();

    import(io);



    /*
     * Event Manager
     */
    eventManager = make_unique<EventManager>();

    /*
     * Setting up the Models
     */
    unique_ptr<PieceModel> pieceModel = make_unique<PieceModel>(*game, *eventManager);
    unique_ptr<CaseModel> caseModel = make_unique<CaseModel>(*game, *eventManager);

    /*
     * Value Variable Choices
     */
    unique_ptr<VariableInterface>
        variableInterface = make_unique<CaseRowscanVariable>(*pieceModel); // creating variable
    unique_ptr<ValueInterface> valueInterface = make_unique<PieceNormalValue>(*caseModel); // Creating value

    /*
     * PathFinder
     */
    pathFinder = make_unique<PathFinder>(move(variableInterface), move(valueInterface));

    /*
     * Constraints
     */
    unique_ptr<CasePieceConstraint>
        casePieceConstraint = make_unique<CasePieceConstraint>(*caseModel, *pieceModel, *eventManager);

    /*
     * Solver
     */
    solver = make_unique<CasePieceSolver>(*pathFinder, *casePieceConstraint, models, *game);

    /*
     * Storing
     */
    constraints.push_back(move(casePieceConstraint));

    models.push_back(move(pieceModel));
    models.push_back(move(caseModel));
}

void Framework::import(IO &io)
{
    int current_number;
    int placed_pieces;

    // taille du jeu
    io >> current_number;
    game->setSize(current_number);

    // nombre de couleurs;
    io >> current_number;

    // nombre de pieces pre-placees
    io >> placed_pieces;

    for (int i = 0; i < placed_pieces; i++) {
        for (int j = 0; j < 4; ++j) {
            // on ignore ces données
            io >> current_number;
        }
    }

    for (int id = 0; id < game->depth; ++id) {
        unique_ptr<PieceImportData> piece = make_unique<PieceImportData>();
        int zero_count = 0;


        for (int i = 0; i < 4; ++i) {
            io >> current_number;
            // DEBUG :
            // cout << current_number << " ";

            if (current_number == 0) {
                ++zero_count;
            }

            piece->colors[0][i] = current_number;

        }

        for (int i = 0; i < 4; ++i) {
            for (int j = 1; j <= 3; ++j) {
                piece->colors[j][(j + i) % 4] = piece->colors[0][i];
            }
        }

        piece->id = id;
        piece->type = zero_count;
        // DEBUG :
        // cout << endl;

        game->pieces[id] = move(piece);
    }
}
