//
// Created by stardisblue on 12/02/16.
//

#ifndef COROLLE_H
#define COROLLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#include "Piece.h"
#include "Jeu.h"

class Corolle
{
private:
    Piece pieces[Jeu::JEU_PIECES_MAX];
    int rotation;
    int size;
    int type;
    int hamming;

public:
    static const int C = 0;
    static const int BC = 1;
    static const int B = 2;
    static const int IBB = 3;
    static const int IB = 4;
    static const int I = 5;

    static const int HAMMING_1 = 1;
    static const int HAMMING_2 = 2;
    static const int HAMMING_3 = 3;

    static const int SIZE_C_1 = 3;
    static const int SIZE_C_2 = 6;
    static const int SIZE_C_3 = 10;

    static const int SIZE_B_1 = 4;
    static const int SIZE_B_2 = 9;
    static const int SIZE_B_3 = 16;

    static const int SIZE_I_1 = 5;
    static const int SIZE_I_2 = 13;
    static const int SIZE_I_3 = 25;

    Corolle();

    Corolle(const Piece pieces[], int size, int type, int hamming);

    Corolle(const Corolle &corolle);

    ~Corolle()
    { };

// Getters and Setters

    void setPieces(Piece *pieces);

    void setHamming(int hamming);

    void setRotation(int rotation);

    void setType(int type);

    void setSize(int size);

    const Piece *getPieces() const;

    const int getHamming() const;

    const int getRotation() const;

    const int getType() const;

    const int getSize() const;

    const string toString();
};


#endif //COROLLE_H
