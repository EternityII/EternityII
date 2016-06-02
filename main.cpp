#include <iostream>

using namespace std;

#include "Corolle.h"
#include "Generator.h"
#include "File/FileIn.h"

int main()
{
    for (int i = 4; i < 8; ++i) {
        ostringstream str;
        str << "assets/pieces_" << i << "x" << i << ".txt";
        FileIn file_in(str.str().c_str());
        Jeu jeu = file_in.initJeu();
        Generator generator(jeu);
        generator.multipleGeneration();
    }
}
