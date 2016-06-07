//
// Created by stardisblue on 07/06/16.
//

#include "DataManager.h"

void DataManager::add(DataTypeInterface &dataType)
{
    datatypes.push_back(dataType);
}

void DataManager::remove(int dataTypeIndex)
{
    datatypes.erase(datatypes.begin() + dataTypeIndex);
}

void DataManager::accept(VariableData &variableData, ValueData &valueData)
{
    //todo
}

void DataManager::discard(VariableData &variableData, ValueData &valueData)
{
    //todo
}

void DataManager::rollback(int &depth)
{
    //TODO:
    for (int i = 0; i < datatypes.size(); ++i) {
        datatypes[depth].rollback(depth);
    }
}
