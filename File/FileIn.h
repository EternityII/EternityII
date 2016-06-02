#ifndef FILE_IN_H
#define FILE_IN_H


#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "../Jeu.h"


using namespace std;

class FileIn
{

public:

    //File *file;
    string path_file;
    ifstream in_file;
    int size;

    FileIn(int taille);

    FileIn(int taille, string path);

    FileIn(string path);

    Jeu initJeu();

private:
    const string getFileName() const;

};

#endif
