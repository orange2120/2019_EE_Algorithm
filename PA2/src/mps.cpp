#include <iostream>
#include "maxPlanarSubset.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "[ERROR] Invalid parameters!\n";
        cerr << "Usage: /mps <inputfilename> <outputfilename>\n";
        exit(-1);
    }

    MPS mps;

    mps.readFile(argv[1]);
    // mps.printAdjMatrix();
    mps.process();
    // mps.printAuxMatrix();
    mps.writeFile(argv[2]);
}