#include <string>
#include "EternityII.h"

using namespace std;

int main(int argc, const char *argv[])
{
    string filename = "assets/pieces_5x5.txt";

    /**
     * 0 : Rowscan
     * 1 : Diagonal
     * 2 : Optimist
     * 3 : Pessimist
     */
    int variable = 0;
    /**
     * 0 : Lexico
     * 1 : Optimist
     * 2 : Pessimist
     */
    int value = 2;

    EternityII e2;
    e2.bootstrap(filename, variable, value);
}