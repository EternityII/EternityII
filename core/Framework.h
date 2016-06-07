#ifndef ETERNITYII_FRAMEWORKMANAGER_H
#define ETERNITYII_FRAMEWORKMANAGER_H

#include <string>
#include "io/IO.h"
#include "structures/GameData.h"
#include "iterations/VariableInterface.h"
#include "data/DataTypeInterface.h"
#include "DataManager.h"
#include "PathFinder.h"
#include "Solver.h"
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

    shared_ptr<PathFinder> pathFinder;

    shared_ptr<Solver> solver;

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
    ValueInterface createValue(int &value);

    /**
     * Creates the Value strategy
     */
    VariableInterface createVariable(int &variable);
};


#endif //ETERNITYII_FRAMEWORKMANAGER_H
