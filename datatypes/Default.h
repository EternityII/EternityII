#ifndef ETERNITYII_DEFAULT_H
#define ETERNITYII_DEFAULT_H

#include "../core/datatype/DataTypeInterface.h"

class Default: public DataTypeInterface
{
public:
    /**
     * On initialisation
     */
    void initialisation(GameData &game);

    /**
     * When a Piece is put on the plate
     */
    void accept(ValueData &valueData, VariableData &variableData);

    /*
     * When a piece is taken out from the game
     */
    void discard(ValueData &valueData, VariableData &variableData);

    /**
     * When the iteration is rolledback
     */
    void rollback(int &depth);
};


#endif //ETERNITYII_DEFAULT_H
