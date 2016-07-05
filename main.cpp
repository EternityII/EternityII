#include <string>
#include "Framework.h"

using namespace std;


int main(int argc, const char *argv[])
{
    string filename = "/home/stardisblue/Documents/Eternity/EternityII/assets/pieces_4x4.txt";
    int variable = 0;
    int value = 0;

    Framework framework;
    framework.bootstrap(filename, variable, value);
}