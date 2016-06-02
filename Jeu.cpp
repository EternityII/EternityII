#include "Jeu.h"

Jeu::Jeu(const int sizeJeu)
    : size(sizeJeu)
{
    nb_pieces_presentes = 0;
    nb_pieces_tabC = 0;
    nb_pieces_tabB = 0;
    nb_pieces_tabI = 0;
}

void Jeu::addPiece(Piece &p)
{

    if (nb_pieces_presentes < (size * size)) {
        jeu[nb_pieces_presentes] = p;
        nb_pieces_presentes++;

        if (p.getType() == Piece::BORD) {
            tab_b[nb_pieces_tabB] = p;
            nb_pieces_tabB++;
        } else if (p.getType() == Piece::COIN) {
            tab_c[nb_pieces_tabC] = p;
            nb_pieces_tabC++;
        } else if (p.getType() == Piece::INTERIEUR) {
            tab_i[nb_pieces_tabI] = p;
            nb_pieces_tabI++;
        }
    }
}

// Getters 
int Jeu::getSize()
{
    return size;
}

Piece *Jeu::getJeu()
{
    return jeu;
}

Piece *Jeu::getTabC()
{
    return tab_c;
}

Piece *Jeu::getTabB()
{
    return tab_b;
}

Piece *Jeu::getTabI()
{
    return tab_i;
}
