#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class FileUtils
{
private:
    string file_name;
public:
    FileUtils();

    virtual const string getFileName();
};

#endif //FILEUTILS_H
