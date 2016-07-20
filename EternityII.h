#ifndef ETERNITYII_ETERNITYII_H
#define ETERNITYII_ETERNITYII_H


#include <vector>
#include <string>
#include "core/io/IO.h"
#include "core/io/data/GameImportData.h"
#include "core/pathfinder/PathFinder.h"
#include "core/SolverInterface.h"

using namespace std;

/**
 * Stores everything about the program
 */
class EternityII
{
public:

    static const int CPCONSTRAINT = 0;
    /**
     * Initializes EternityII
     *
     * @param string &filename ...
     * @param int &variable : the variable strategy
     * @param int &value : the value strategy
     */
    void bootstrap(string &filename, int &variable, int &value);

private:
    /**
     * In charge of the pathfinding
     */
    unique_ptr<PathFinder> pathFinder;

    /**
     * In charge of the solving
     */
    unique_ptr<SolverInterface> solver;

    /**
     * In charge of game information
     */
    unique_ptr<GameImportData> gameImport;

    /**
     * In charge of the event queue
     */
    unique_ptr<EventManager> eventManager;

    /**
     * storage for the constraints
     */
    vector<unique_ptr<ConstraintInterface>> constraints;

    /**
     * storage for the models
     */
    vector<unique_ptr<ModelInterface>> models;

    /**
     * Imports into gameImport from IO object
     *
     * @param IO &io : ...
     */
    void import(IO &io);

};


#endif //ETERNITYII_ETERNITYII_H
