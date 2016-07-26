#ifndef ETERNITYII_IO_H
#define ETERNITYII_IO_H

#include <fstream>
#include <memory>

using namespace std;

class IO
{
private:
    unique_ptr<fstream> file;

public:

    /**
     * Open the file, returns an error if failed
     *
     * @param string filename, the filename
     * @param ios_base::openmode mode, the openmode
     */
    IO(string &filename, ios_base::openmode mode = ios_base::in | ios_base::out)
    {
        file = make_unique<fstream>(filename.c_str(), mode);

        if (not file->good()) {
            perror("The file couldn't be opened");
            exit(EXIT_FAILURE);
        }
    };

    ~IO()
    {
        close();
    }

    /**
     * Closes the file
     */
    void close()
    {
        if (file->is_open()) {
            file->close();
        }
    }

    /**
     * Operator overload, mirror of fstream::operator>>
     */
    IO &operator>>(string &str)
    {
        *file >> str;

        return *this;
    }
    /**
     * Operator overload, mirror of fstream::operator<<
     */
    IO &operator<<(string &str)
    {
        *file << str;

        return *this;
    }

    /**
     * Operator overload, mirror of fstream::operator>>
     */
    IO &operator>>(int &number)
    {
        *file >> number;

        return *this;
    }

    /**
     * Operator overload, mirror of fstream::operator<<
     */
    IO &operator<<(int &number)
    {
        *file << number;

        return *this;
    }
};

#endif //ETERNITYII_IO_H
