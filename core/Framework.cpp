#include <iostream>
#include "Framework.h"


void Framework::bootstrap(string &filename, int &variable, int &value)
{
    IO io(filename, ios::in);

    import(io);

    ValueInterface valueInterface = createValue(value);
    VariableInterface variableInterface = createVariable(variable);

    pathFinder = make_shared(new PathFinder(valueInterface, variableInterface));
    solver = make_shared(new Solver(*pathFinder, dataManager));

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
        unique_ptr<PieceData> piece = make_unique<PieceData>();
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

ValueInterface Framework::createValue(int &value)
{
    return ValueInterface();
}

VariableInterface Framework::createVariable(int &variable)
{
    return VariableInterface();
}
