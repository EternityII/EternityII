#ifndef JEU_H
#define JEU_H

#include <math.h>
#include <iostream>

#include "Piece.h"


class Jeu
{

public:

    static const int JEU_SIZE_MAX = 16;
    static const int JEU_PIECES_MAX = 256;

    Jeu(const int size); //constructeur

    ~Jeu()
    { }

    void addPiece(Piece &p); //Ajout d'une piece dans le jeu

    //Getters
    int getSize();

    Piece *getJeu();

    Piece *getTabC();

    Piece *getTabB();

    Piece *getTabI();

private:

    int size;
    Piece jeu[JEU_PIECES_MAX];
    Piece tab_c[4];
    Piece tab_b[(JEU_SIZE_MAX - 2) * 4];
    Piece tab_i[(JEU_SIZE_MAX - 2) * (JEU_SIZE_MAX - 2)];

    int nb_pieces_presentes;
    int nb_pieces_tabC;
    int nb_pieces_tabB;
    int nb_pieces_tabI;

};

#endif
