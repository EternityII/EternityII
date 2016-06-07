//
// Created by stardisblue on 06/06/16.
//

#ifndef ETERNITYII_PIECESTRUCT_H
#define ETERNITYII_PIECESTRUCT_H

#include <vector>

using namespace std;

struct PieceData
{
    int id;
    int type;

    vector<vector<int>> colors;

    PieceData()
    {
        colors.resize(4, vector<int>(4, 0));
    }
};

#endif //ETERNITYII_PIECESTRUCT_H
