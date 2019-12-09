#ifndef _CYCLEBREAKING_H_
#define _CYCLEBREAKING_H_

#include <iostream>
#include <fstream>
using namespace std;

class CycleBreaking
{
  public:
      CycleBreaking();
      ~CycleBreaking();
      void processing();
      bool readFile(const char *);
      bool writeFile(const char *);


  private:
    bool isDirected = false;
    uint32_t nVertices = 0;
    uint32_t nEdges = 0;
};

#endif // _CYCLEBREAKING_H_