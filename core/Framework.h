#ifndef ETERNITYII_FRAMEWORKMANAGER_H
#define ETERNITYII_FRAMEWORKMANAGER_H


#include <memory>
#include "DataManager.h"
#include "PathFinder.h"
#include "Solver.h"
#include "structures/GameData.h"
#include "io/IO.h"
#include "pathfinder/ValueInterface.h"
#include "pathfinder/VariableInterface.h"

using namespace std;

class Framework
{
public:
    /**
     * Initialise le Framework d'EternityII
     */
    void bootstrap(string &filename, int &value, int &variable);

private:
    DataManager dataManager;

    PathFinder pathFinder;

    Solver solver;

    GameData game;

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
