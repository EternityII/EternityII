#ifndef ETERNITYII_FRAMEWORKMANAGER_H
#define ETERNITYII_FRAMEWORKMANAGER_H


#include <vector>
#include <string>
#include "core/io/IO.h"
#include "core/pathfinder/PathFinder.h"
#include "app/solver/PieceCaseSolver.h"
#include "app/pathfinder/value/PieceNormalValue.h"
#include "app/pathfinder/variable/CaseRowscanVariable.h"

using namespace std;

template<class VarM, class ValM, class VarD, class ValD>
class Framework
{
public:
    /**
     * Initialise le Framework d'EternityII
     */
    void bootstrap(string &filename, int &variable, int &value)
    {
        IO io(filename, ios::in);

        import(io);

        // Creating the solver
        solver = make_unique<PieceCaseSolver>();

        // Setting up the PathFinder
        pathFinder.set(move(createValue(value)));
        pathFinder.set(move(createVariable(variable)));

        // Initializing the models
        unique_ptr<PieceModel> pieceModel = make_unique<PieceModel>();
        unique_ptr<CaseModel> caseModel = make_unique<CaseModel>();

        // Creating the constraint
        unique_ptr<CasePieceConstraint> pieceCaseConstraint = make_unique<CasePieceConstraint>();

        pieceCaseConstraint->setFirst(*caseModel);
        pieceCaseConstraint->setSecond(*pieceModel);

        // initializing the solver
        solver->initialize(pathFinder, *pieceCaseConstraint);

        // storing the constraints
        constraints.push_back(move(pieceCaseConstraint));

        // storing the models
        models.push_back(move(pieceModel));
        models.push_back(move(caseModel));

        // initializing the models ... akward
        for (int i = 0; i < models.size(); ++i) {
            models[i]->initialize(game);
        }

        // go go power rangers !!
        solver->resolve();
    }

private:
    PathFinder<VarD, ValD> pathFinder;

    unique_ptr<SolverInterface<VarM, ValM, VarD, ValD>> solver;

    GameImportData game;

    vector<unique_ptr<ConstraintInterface<VarM, ValM, VarD, ValD>>> constraints;

    vector<unique_ptr<ModelInterface<VarD, ValD>>>
        models;

    /**
     * @param io, the file which contains the game data
     *
     * imports the game data
     */
    void import(IO &io)
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

        for (int id = 0; id < game.depth; ++id) {
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

    /**
     * Creates the Value strategy
     */
    unique_ptr<ValueInterface<VarD, ValD>> createValue(int &value)
    {
        if (false) {
        } else {
            unique_ptr<ValueInterface<VarD, ValD>> valueInterface = make_unique<PieceNormalValue>();
            return move(valueInterface);
        }
    }

    /**
     * Creates the Value strategy
     */
    unique_ptr<VariableInterface<VarD, ValD>> createVariable(int &variable)
    {
        if (false) {

        } else {
            unique_ptr<VariableInterface<VarD, ValD>> variableInterface = make_unique<CaseRowscanVariable>();
            return move(variableInterface);
        }
    }

};


#endif //ETERNITYII_FRAMEWORKMANAGER_H
