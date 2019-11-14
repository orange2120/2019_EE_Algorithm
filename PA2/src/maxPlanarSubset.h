#ifndef __MAXPLANNERSUBSET_H__
#define __MAXPLANNERSUBSET_H__

#include <iostream>
#include <fstream>
using namespace std;

class MPS
{
  public:
    MPS();
    ~MPS();
    bool readFile(const char *);
    bool writeFile(const char *);
    void process();
    void printAdjMatrix();
    void printAuxMatrix();

  private:
    int _nVertices = 0;
    int _maxChords = 0;
    int *_testChord;
    bool **_inChordMatrix;
    bool **_outChordMatrix;
    int **_auxMatrix = 0;
};

#endif