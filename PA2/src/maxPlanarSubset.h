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
    void backtrack(int, int);
    void printAdjMatrix() const;
    void printAuxMatrix() const;

  private:
    int _nVertices = 0;
    int *_chordTable;      // store the chords with vertice numbers
    int **_auxMatrix;      // MIS(i, j) table for dynamic programming
    bool *_maxChordTable;
};

#endif