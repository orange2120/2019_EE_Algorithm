#ifndef _CYCLEBREAKING_H_
#define _CYCLEBREAKING_H_

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

struct Edge
{
  int u;
  int v;
  int16_t weight;

  bool operator<(const Edge &e) const
  {
    return (this->weight < e.weight);
  }
};

class Graph
{
  public:
    Graph(uint32_t &);
    ~Graph();
    void addEdge(int &, int &, int16_t &);
    void removeNonDec(vector<Edge> &);
    bool isConnected();
    void findCycleDFS(int, int, int &, uint8_t *, int *, int *);
    bool hasCycle();
    void printVertices() const;
    void printEdges() const;
    void printCycle(vector<int> &) const;

  private:
    void DFS(int, bool *);
    uint32_t _nVertices = 0;
    list<int> *_adj; // adjacency list of vertices, 1D array of list
    vector<Edge> _edges;
};

class CycleBreaking
{
  public:
      CycleBreaking();
      ~CycleBreaking() {};
      void processing();
      void processingDirected();
      void processingUnirected();
      bool readFile(const char *);
      bool writeFile(const char *);
      void reportGraph() const;

  private:
    bool _isDirected = false;
    uint32_t _nEdges = 0;
    int _rmWeightSum = 0;
    Graph *_graph;
    vector<Edge> _removedEdges;

};

#endif // _CYCLEBREAKING_H_