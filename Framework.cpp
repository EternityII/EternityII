#include "Framework.h"
#include "app/pathfinder/value/PieceNormalValue.h"
#include "app/pathfinder/variable/CaseRowscanVariable.h"

void Framework::bootstrap(string &filename, int &variable, int &value)
{
    IO io(filename, ios::in);

    import(io);

    solver = make_unique<PieceCaseSolver>();

    pathFinder.set(move(createValue(value)));
    pathFinder.set(move(createVariable(variable)));

    unique_ptr<PieceModel> pieceModel = make_unique<PieceModel>();
    unique_ptr<CaseModel> caseModel = make_unique<CaseModel>();

    unique_ptr<PieceCaseConstraint> pieceCaseConstraint = make_unique<PieceCaseConstraint>();

    pieceCaseConstraint->setFirst(*pieceModel);
    pieceCaseConstraint->setSecond(*caseModel);

    solver->initialize(pathFinder, *pieceCaseConstraint);

    constraints.push_back(move(pieceCaseConstraint));

    modeles.push_back(move(pieceModel));
    modeles.push_back(move(caseModel));

    for (int i = 0; i < modeles.size(); ++i) {
        modeles[i]->initialize(game);
    }

    //dataManager.initialize();
    solver->resolve();
}

/**
 * Importe les pièces depuis le fichier d'entree
 */
void Framework::import(IO &io)
{
    int current_number;
    int placed_pieces;

    // taille du jeu
    io >> current_number;
    game.setSize(current_number);

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

    for (int id = 0; id < game.piecesQte; ++id) {
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

        game.pieces[id] = move(piece);
    }
}

unique_ptr<ValueInterface> Framework::createValue(int &value)
{
    if (false) {
    } else {
        unique_ptr<ValueInterface> valueInterface = make_unique<PieceNormalValue>();
        return move(valueInterface);
    }
}

unique_ptr<VariableInterface> Framework::createVariable(int &variable)
{
    if (false) {

    } else {
        unique_ptr<VariableInterface> variableInterface = make_unique<CaseRowscanVariable>();
        return move(variableInterface);
    }
}
