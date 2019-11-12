#ifndef __MAXPLANNERSUBSET_H__
#define __MAXPLANNERSUBSET_H__

#include <iostream>
#include <fstream>
using namespace std;

class MPS
{
  public:
    MPS();
    bool readFile(const char *);
    bool writeFile(const char *);
    void process();
    void printAdjMatrix();

  private:
    int _nChords = 0;
    int _outChords = 0;
    bool **_inChordMatrix;
    bool **_outChordMatrix;
    int **_auxMatrix = 0;
};

#endif