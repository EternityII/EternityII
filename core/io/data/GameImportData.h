#ifndef ETERNITYII_GAMEIMPORTDATA_H
#define ETERNITYII_GAMEIMPORTDATA_H

#include <memory>
#include "PieceImportData.h"

using namespace std;

class GameImportData
{
public:
    //! the number of pieces / cases
    int depth;

    //! the number of pieces. Duplication of #depth to clarify
    int casesQte;

    //! the number of cases. Duplication of #depth to clarify
    int piecesQte;

    //! size of the instance (heigh or width)
    int size;

    //! the number of unique colors
    int colorsQte;

    vector<int> colorCount;
    //! unused : the instance. may be implemented later for visual representation
    vector<vector<PieceImportData>> plateau;

    //! list of the pieces, with four precalculated rotation
    vector<unique_ptr<PieceImportData>> pieces;

    /**
     * Sets the size of the game.
     *
     * Set the #depth (also #piecesQte and #casesQte), and the #size as well,
     * also pre-sizes the list of #pieces
     *
     * @param newSize the size of the game
     */
    void setSize(const int &newSize)
    {
        size = newSize;
        depth = newSize * newSize;
        piecesQte = depth;
        casesQte = depth;

        pieces.resize(piecesQte);
    }

};


#endif //ETERNITYII_GAMEIMPORTDATA_H
