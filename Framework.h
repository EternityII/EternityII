#ifndef ETERNITYII_FRAMEWORKMANAGER_H
#define ETERNITYII_FRAMEWORKMANAGER_H


#include <vector>
#include <string>
#include "core/io/IO.h"
#include "core/pathfinder/PathFinder.h"
#include "app/solver/CasePieceSolver.h"
#include "app/pathfinder/value/PieceNormalValue.h"
#include "app/pathfinder/variable/CaseRowscanVariable.h"
#include "core/io/data/GameImportData.h"

using namespace std;

class Framework
{
public:
    /**
     * Initialise le Framework d'EternityII
     */
    void bootstrap(string &filename, int &variable, int &value);

private:
    unique_ptr<PathFinder> pathFinder;

    unique_ptr<SolverInterface> solver;

    unique_ptr<GameImportData> game;

    unique_ptr<EventManager> eventManager;

    vector<unique_ptr<ConstraintInterface>> constraints;

    vector<unique_ptr<ModelInterface>> models;

    void import(IO &io);

};


#endif //ETERNITYII_FRAMEWORKMANAGER_H
