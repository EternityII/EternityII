#ifndef ETERNITYII_PIECEIMPORTDATA_H
#define ETERNITYII_PIECEIMPORTDATA_H

#include <vector>

using namespace std;

class PieceImportData
{
public:
    int id;
    int type;

    vector<vector<int>> colors;

    PieceImportData()
    {
        colors.resize(4, vector<int>(4, 0));
    }

    ~PieceImportData()
    { }
};

#endif //ETERNITYII_PIECEIMPORTDATA_H
