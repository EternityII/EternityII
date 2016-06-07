//
// Created by stardisblue on 07/06/16.
//

#ifndef ETERNITYII_DATATYPEINTERFACE_H
#define ETERNITYII_DATATYPEINTERFACE_H

#include "../structures/GameData.h"
#include "../structures/ValueData.h"
#include "../structures/VariableData.h"

class DataTypeInterface
{
public:
    /**
     * On initialisation
     */
    virtual void initialisation(GameData &game) = 0;

    /**
     * When a Piece is put on the plate
     */
    virtual void accept(ValueData &valueData, VariableData &variableData) = 0;

    /*
     * When a piece is taken out from the game
     */
    virtual void discard(ValueData &valueData, VariableData &variableData) = 0;

    /**
     * When the iteration is rolledback
     */
    virtual void rollback(int &depth) = 0;

protected:

    StateData actualState;

    vector<StateData> snapshotStates;

};

#endif //ETERNITYII_DATATYPEINTERFACE_H
