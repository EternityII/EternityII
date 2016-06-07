//
// Created by stardisblue on 07/06/16.
//

#ifndef ETERNITYII_DATAMANAGER_H
#define ETERNITYII_DATAMANAGER_H


#include "structures/VariableData.h"
#include "structures/ValueData.h"
#include "datatype/DataTypeInterface.h"
class DataManager
{
public:

    void add(DataTypeInterface &dataType);

    void remove(int dataTypeIndex);

    void accept(VariableData &variableData, ValueData &valueData);

    void discard(VariableData &variableData, ValueData &valueData);

    void rollback(int &depth);

private:
    vector<DataTypeInterface> datatypes;
};


#endif //ETERNITYII_DATAMANAGER_H
