#include "FileIn.h"


FileIn::FileIn(int taille, string path)
    : size(taille), path_file(path)
{ }

FileIn::FileIn(int taille)
    : size(taille)
{
    path_file = getFileName();
}

FileIn::FileIn(string path)
    : path_file(path)
{

}

Jeu FileIn::initJeu()
{
    //Ouverture du fichier
    in_file.open(this->path_file.c_str(), ios::out);

    if (!in_file.good()) {
        exit(EXIT_FAILURE);
    }

    cout << "# Lecture Fichier " << path_file << endl << endl;

    int couleur[4];
    int color = 0;

    string str = " "; // 4 premieres lignes
    in_file >> size;
    Jeu jeu(size);

    for (int i = 0; i < 4; i++) {
        getline(in_file, str);
        // cout << str << endl;
    }

    for (int i = 0; i < (size * size); i++) {
        // cout << i << endl;
        for (int j = 0; j < 4; j++) {
            in_file >> color;
            couleur[j] = color;
        }

        Piece p(i, couleur);
        jeu.addPiece(p);

    }

    in_file.close();

    return jeu;
}

const string FileIn::getFileName() const
{
    ostringstream s;// Barbarisme a l'état pur
    s << "./assets/pieces_" << size << "x" << size << ".txt";
    return s.str();
}
