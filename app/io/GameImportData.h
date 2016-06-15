#ifndef ETERNITYII_GAMEIMPORTDATA_H
#define ETERNITYII_GAMEIMPORTDATA_H

#include <vector>
#include <memory>
#include "PieceImportData.h"

using namespace std;

class GameImportData
{
public:
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
    vector<vector<PieceImportData>> plateau;

    /**
     * Liste des pièces
     */
    vector<unique_ptr<PieceImportData>> pieces;

    void setSize(int &i)
    {
        size = i;
        piecesQte = i * i;

        pieces.resize(piecesQte);
    }
};


#endif //ETERNITYII_GAMEIMPORTDATA_H
