#include "Piece.h"

Piece::Piece()
    : couleur{0, 0, 0, 0}
{
    id = -1;
    rotation = 0;
}

Piece::Piece(const int idPiece, int couleur[4])
{
    id = idPiece;
    rotation = 0;
    for (int i = 0; i < 4; ++i) {
        this->couleur[i] = couleur[i];
    }
    //Compte le nombre de Zero afin de definir le type
    int nb_zero = 0;

    for (int i = 0; i < 4; i++) {
        if (couleur[i] == 0) {
            nb_zero++;
        }
    }

    if (nb_zero == 0) {
        type = INTERIEUR;
    } else if (nb_zero == 1) {
        type = BORD;
    } else if (nb_zero == 2) {
        type = COIN;
    }
}

const string Piece::toString()
{
    ostringstream s;
    s << id;
    return s.str();
}

string Piece::toStringDetail() const
{
    ostringstream stream;
    stream << "Pièce n " << id << endl;
    return stream.str();
}

const int Piece::getColor(const int position)
{
    if (position > 4) {
        return -1;
    }

    return couleur[(position + rotation) % 4];
}

//Getters
const int Piece::getRotation()
{
    return rotation;
}

const int *Piece::getTabCouleur()
{
    return couleur;
}

const int Piece::getType()
{
    return type;
}

//Setters
void Piece::setRotation(const int new_rotation)
{
    rotation = new_rotation;
}

void Piece::setTabCouleur(const int new_tab_couleur[4])
{
    for (int i = 0; i < 5; ++i) {
        couleur[i] = new_tab_couleur[i];
    }
}

int Piece::operator[](const int &position)
{
    return getColor(position);
}

