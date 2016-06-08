#ifndef ETERNITYII_GAMEDATA_H
#define ETERNITYII_GAMEDATA_H

#include <vector>
#include <memory>

#include "PieceData.h"

using namespace std;

struct GameData
{
    /**
     * Nombre de pièces
     */
    int piecesQte;

    /**
     * Taille du plateau
     */
    int size;

    /**
     * Plateau
     */
    vector<vector<PieceData>> plateau;

    /**
     * Liste des pièces
     */
    vector<unique_ptr<PieceData>> pieces;

    void setSize(int &i)
    {
        size = i;
        piecesQte = i * i;

        pieces.resize(piecesQte);
    }
};


#endif //ETERNITYII_GAMEDATA_H
