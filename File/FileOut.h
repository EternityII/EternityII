#ifndef FILEOUT_H
#define FILEOUT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


using namespace std;

#include "../Corolle.h"
#include "FileUtils.h"

class FileOut: public FileUtils
{
public:
    int size;
    int corolle_hamming;
    int corolle_type;
    int piece_number;
    int rotation;
    int corolle_size;
    ofstream fichier;

    FileOut()
    { };

    ~FileOut()
    { };

    FileOut(int size, int corolle_hamming, int corolle_type, int piece_number,
        int rotation, int corolle_size);

    void open();

    bool isOpen()
    { return fichier.is_open(); };

    void put(Corolle &corolle);

    void close();

    const string getFileName() const;
};

#endif //FILEOUT_H

