#ifndef ETERNITYII_DATABRIDGE_H
#define ETERNITYII_DATABRIDGE_H

#include "DataTypeInterface.h"
#include "../structures/GameData.h"
#include "state/DataBridgeStateData.h"

class DataBridge: public DataTypeInterface
{
public:
    DataBridge(const GameData &game);

    DataBridge(DataBridge &dataBridge);

    /**
     * When a Value is accepted as a possibility (accepted) for the Variable
     */
    void accept(ValueData &valueData, VariableData &variableData)
    {

    };

    /*
     * When a Value is discarded as a possibility for the Variable
     */
    void discard(ValueData &valueData, VariableData &variableData)
    {

    };

    /**
     * When the iteration is rolledback
     */
    void rollback(int &depth)
    {

    };

private:
    DataBridgeStateData actualState;
};


#endif //ETERNITYII_DATABRIDGE_H

