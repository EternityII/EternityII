/*
 * Created by stardisblue on 12/02/16.
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>
#include <time.h>

#include "Jeu.h"
#include "Corolle.h"
#include "File/FileOut.h"


class Generator
{
public:
    static const int PARCOURS_ROW = 0;
    static const int PARCOURS_DIAGONAL = 1;
    static const int PARCOURS_SPIRALE_IN = 2;
    static const int PARCOURS_SPIRALE_OUT = 3;
    static const int PARCOURS_DYNAMIQUE_OPTIMISTE = 4;
    static const int PARCOURS_DYNAMIQUE_PESSIMISTE = 5;
    static const int PARCOURS_MAX = 6;

    static const int VAL_NORMAL = 0;
    static const int VAL_OPTIMISTE = 1;
    static const int VAL_PESSIMISTE = 2;
    static const int VAL_MAX = 3;

    Generator(Jeu jeu);

    void multipleGeneration();

    void parcoursBruteForce(const int type_parcours, const int type_variable);
private:

    static const int POS_X = 0;

    static const int POS_Y = 1;
    static const int POS_TYPE = 2;
    static const int POS_TYPE_COIN_NW = 1;

    static const int POS_TYPE_COIN_NE = 2;
    static const int POS_TYPE_COIN_SE = 3;
    static const int POS_TYPE_COIN_SW = 4;
    static const int POS_TYPE_COIN = 5;
    static const int POS_TYPE_BORD = 10;

    static const int POS_TYPE_BORD_TOP = 11;
    static const int POS_TYPE_BORD_LEFT = 12;
    static const int POS_TYPE_BORD_BOTTOM = 13;
    static const int POS_TYPE_BORD_RIGHT = 14;
    static const int POS_TYPE_INTERIEUR = 6;

    static const int JEU_SIZE_MAX = 16;

    static const int JEU_PIECES_MAX = 256;
    static const int SE = 0;

    static const int SW = 1;
    static const int NW = 2;
    static const int NE = 3;
    static const int N = 0;

    static const int E = 1;
    static const int S = 2;
    static const int W = 3;
    clock_t start;

    Jeu jeu;

    int jeu_size;
    Piece plateau[JEU_SIZE_MAX][JEU_SIZE_MAX];

    bool disponibles[JEU_PIECES_MAX];
    int coordonnees[100][3];

    int taille_plateau;

    long long nb_noeuds;
    long long nb_solutions;

    int type_parcours;
    int type_variable;

    void parcoursBruteForce();

    void placerPieceRecursion(int &position, int coord_x, int coord_y, int position_type, Piece &piece_coin);

    void diagonalWalker(int &position_nb, int &x, int &y, const int orientation, const int &length);

    void straightWalker(int &position_nb, int &x, int &y, const int orientation, const int &length);

    void coordinatesCreator();

    void addCoordinate(int &position_nb, const int &x, const int &y);

    const int pieceTypeByPosition(const int &x, const int &y);

    const bool compareColors(Piece &a, Piece &b, const int side_a, const int side_b);

    const bool compareSides(Piece &piece, const int &x, const int &y, const int side_to_compare);

    const bool canPutPiece(Piece &piece, const int &x, const int &y, const int position_type);

    void putPiece(const int &x, const int &y, Piece &piece);

    void pickOffPiece(const int &numero_piece, const int &x, const int &y);

    void generationRecursive(int &position);
    void putPieceEvent();
    void pickOffPieceEvent();

    void solutionFoundEvent();

    void coordinateChooser(const int &position, int &position_type, int &coord_x, int &coord_y) const;

    string getNomParcours() const;
};


#endif //GENERATOR_H
