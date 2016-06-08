#ifndef ETERNITYII_DATABRIDGESTATEDATA_H
#define ETERNITYII_DATABRIDGESTATEDATA_H


#include "StateData.h"

struct DataBridgeStateData: public StateData
{

    DataBridgeStateData()
    { }

    DataBridgeStateData(DataBridgeStateData &dataBridgeStateData)
    {
        qtePiecesByCell = dataBridgeStateData.qtePiecesByCell;
        qteCellsByPiece = dataBridgeStateData.qteCellsByPiece;
        piecesCells = dataBridgeStateData.piecesCells;
    }

    void initialize(const GameData &gameData)
    {
        qteCellsByPiece.resize(gameData.piecesQte);
        qtePiecesByCell.resize(gameData.size, vector<int>(gameData.size));
        piecesCells.resize(gameData.size,
            vector<vector<vector<bool>>>(gameData.size,
                vector<vector<bool>>(gameData.piecesQte,
                    vector<bool>(4))));
    }

    vector<int> qteCellsByPiece;

    vector<vector<int>> qtePiecesByCell;

    vector<vector<vector<vector<bool>>>> piecesCells;
};

#endif //ETERNITYII_DATABRIDGESTATEDATA_H
