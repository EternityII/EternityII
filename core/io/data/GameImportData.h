#ifndef ETERNITYII_GAMEIMPORTDATA_H
#define ETERNITYII_GAMEIMPORTDATA_H

#include <memory>
#include "PieceImportData.h"

using namespace std;

class GameImportData
{
public:
    /**
     * Nombre de pièces
     */
    int depth;

    /**
     * Taille du plateau
     */
    int size;

    /**
     * Plateau
     */
    vector<vector<PieceImportData>> plateau;

    /**
     * Liste des pièces
     */
    vector<unique_ptr<PieceImportData>> pieces;

    void setSize(int &i)
    {
        size = i;
        depth = i * i;

        pieces.resize(depth);
    }

    ~GameImportData()
    { }
};


#endif //ETERNITYII_GAMEIMPORTDATA_H
