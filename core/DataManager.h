#ifndef ETERNITYII_DATAMANAGER_H
#define ETERNITYII_DATAMANAGER_H

#include <memory>

#include "datatype/DataBridge.h"
#include "datatype/DataTypeInterface.h"
#include "structures/VariableData.h"
#include "structures/ValueData.h"
class DataManager
{
public:
    DataManager()
    { }

    void initialize(unique_ptr<DataBridge> dataBridge);

    void add(shared_ptr<DataTypeInterface> dataType);

    void remove(int dataTypeIndex);

    void accept(VariableData &variableData, ValueData &valueData);

    void discard(VariableData &variableData, ValueData &valueData);

    void rollback(int &depth);

private:
    unique_ptr<DataBridge> dataBridge;

    vector<shared_ptr<DataTypeInterface>> datatypes;
};


#endif //ETERNITYII_DATAMANAGER_H
