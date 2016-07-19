#include <string>
#include "EternityII.h"

using namespace std;

int main(int argc, const char *argv[])
{
    string filename = "assets/pieces_5x5.txt";
    int variable = 0;
    int value = 0;

    EternityII e2;
    e2.bootstrap(filename, variable, value);
}