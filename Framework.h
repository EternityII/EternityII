#ifndef ETERNITYII_FRAMEWORKMANAGER_H
#define ETERNITYII_FRAMEWORKMANAGER_H

#include <memory>
#include "core/io/IO.h"
#include "app/solver/PieceCaseSolver.h"
#include "core/ConstraintInterface.h"

using namespace std;

class Framework
{
public:
    /**
     * Initialise le Framework d'EternityII
     */
    void bootstrap(string &filename, int &value, int &variable);

private:
    PathFinder pathFinder;

    unique_ptr<SolverInterface> solver;

    GameImportData game;

    vector<unique_ptr<ConstraintInterface>> constraints;

    vector<unique_ptr<ModelInterface>> modeles;

    /**
     * @param io, the file which contains the game data
     *
     * imports the game data
     */
    void import(IO &io);

    /**
     * Creates the Value strategy
     */
    unique_ptr<ValueInterface> createValue(int &value);

    /**
     * Creates the Value strategy
     */
    unique_ptr<VariableInterface> createVariable(int &variable);
};


#endif //ETERNITYII_FRAMEWORKMANAGER_H
