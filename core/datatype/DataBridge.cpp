#include "DataBridge.h"

DataBridge::DataBridge(const GameData &game)
{
    // initial optimisation
    actualState.initialize(game);

    // corner values have corner variables (pieces)
    for (int i = 0; i < 4; ++i) {
        actualState.qteCellsByPiece[i] = 4;
    }

    // edge values have edge values (pieces)
    int edgeQte = (game.size - 2) * 4;
    for (int i = 4; i < edgeQte + 4; ++i) {
        actualState.qteCellsByPiece[i] = edgeQte;
    }

    //edge variables are edge variables
    actualState.qtePiecesByCell[0][0] = 4;
    actualState.qtePiecesByCell[0][game.size - 1] = 4;
    actualState.qtePiecesByCell[game.size - 1][0] = 4;
    actualState.qtePiecesByCell[game.size - 1][game.size - 1] = 4;

    for (int i = 1; i < game.size - 1; ++i) { // initializing edge variables have edge values
        actualState.qtePiecesByCell[0][i] = edgeQte;
        actualState.qtePiecesByCell[i][0] = edgeQte;
        actualState.qtePiecesByCell[i][game.size - 1] = edgeQte;
        actualState.qtePiecesByCell[game.size - 1][i] = edgeQte;

        for (int val = 4; val < edgeQte + 4; ++val) {
            actualState.piecesCells[0][i][val][0] = true;
            actualState.piecesCells[i][0][val][1] = true;
            actualState.piecesCells[i][game.size - 1][val][3] = true;
            actualState.piecesCells[game.size - 1][i][val][2] = true;
        }
    }

}
DataBridge::DataBridge(DataBridge &dataBridge)
{
    actualState = dataBridge.actualState;
}
