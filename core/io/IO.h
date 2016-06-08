#ifndef ETERNITYII_IO_H
#define ETERNITYII_IO_H

#include <fstream>

using namespace std;

class IO
{
public:

    /**
     * Ouvre le fichier, renvoi une erreur si il y a un problème
     *
     * @param string filename, le nom du fichier
     * @param ios_base::openmode mode le mode
     */
    IO(string &filename, ios_base::openmode mode = ios_base::in | ios_base::out)
    {
        file = make_unique<fstream>(filename.c_str(), mode);

        if (!file->good()) {
            perror("The file cannot be opened");
            exit(EXIT_FAILURE);
        }
    };

    ~IO()
    {
        close();
    }

    void close()
    {
        if (file->is_open()) {
            file->close();
        }
    }

    IO &operator>>(string &str)
    {
        *file >> str;

        return *this;
    }

    IO &operator<<(string &str)
    {
        *file << str;

        return *this;
    }

    IO &operator>>(int &number)
    {
        *file >> number;

        return *this;
    }

    IO &operator<<(int &number)
    {
        *file << number;

        return *this;
    }

    unique_ptr<fstream> file;
};

#endif //ETERNITYII_IO_H
