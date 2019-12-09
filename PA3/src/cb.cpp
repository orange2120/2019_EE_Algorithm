#include <iostream>
#include "CycleBreaking.h"
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "[ERROR] Invalid parameters!\n";
        cerr << "Usage ./cb <inputfilename> <outputfilename>\n";
        exit(EXIT_FAILURE);
    }
    CycleBreaking cb;
    cb.readFile(argv[1]);
    
    cb.writeFile(argv[2]);
}
