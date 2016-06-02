#include "Corolle.h"

using namespace std;

Corolle::Corolle()
{
    size = 4;
    type = 1;
    hamming = 1;
    rotation = 0;
}

Corolle::Corolle(const Piece pieces[], int size, int type, int hamming)
    : size(size), type(type), hamming(hamming)
{
    for (int i = 0; i < size; ++i) {
        this->pieces[i] = pieces[i];
    }

    rotation = pieces[0].rotation;
}

Corolle::Corolle(const Corolle &corolle)
{
    Corolle(corolle.getPieces(), corolle.getSize(), corolle.getType(), corolle.getHamming());
}

const string Corolle::toString()
{
    ostringstream output;
    for (int i = 0; i < size; ++i) {
        output << pieces[i].toString() << " ";
    }
    return output.str();
}


// Getter and Setters

const Piece *Corolle::getPieces() const
{ return this->pieces; }

const int Corolle::getRotation() const
{ return rotation; }

const int Corolle::getHamming() const
{ return hamming; }

const int Corolle::getType() const
{ return type; }

const int Corolle::getSize() const
{ return size; }

void Corolle::setPieces(Piece pieces[Jeu::JEU_PIECES_MAX])
{
    for (int i = 0; i < size; ++i) {
        this->pieces[i] = pieces[i];
    }
}

void Corolle::setRotation(int rotation)
{ this->rotation = rotation; }

void Corolle::setHamming(int hamming)
{ this->hamming = hamming; }

void Corolle::setType(int type)
{ this->type = type; }

void Corolle::setSize(int size)
{ this->size = size; }