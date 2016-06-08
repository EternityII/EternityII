#ifndef ETERNITYII_DATATYPEINTERFACE_H
#define ETERNITYII_DATATYPEINTERFACE_H

#include "../structures/ValueData.h"
#include "../structures/VariableData.h"

class DataTypeInterface
{
public:
    DataTypeInterface()
    { }

    DataTypeInterface(DataTypeInterface &dataTypeInterface)
    { }
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
};

#endif //ETERNITYII_DATATYPEINTERFACE_H
