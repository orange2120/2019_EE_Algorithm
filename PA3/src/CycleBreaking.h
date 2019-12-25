#ifndef _CYCLEBREAKING_H_
#define _CYCLEBREAKING_H_

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

typedef pair<int, int16_t> AdjPair;
typedef pair<int, int> EdgePair;

struct Edge
{
  int u; // from
  int v; // to
  int16_t weight;

  bool operator<(const Edge &e) const
  {
    return (this->weight < e.weight);
  }
};

// template <class T>
struct subset
{
    int parent;
    int rank;
};

class DisjoinSet
{
  public :   
    DisjoinSet(uint32_t &);
    ~DisjoinSet();
    void makeSet();
    int find(int &) const;
    void Union(int &, int &);

  private:  
    uint32_t _nSubset = 0;
    subset *_subs;
};

class Graph
{
  public:
    Graph(uint32_t &);
    ~Graph();
    void addEdge(int &, int &, int16_t &);
    // bool isConnected();
    void printVertices() const;
    void printEdges() const;
    void printCycle(vector<int> &) const;
    void KruskalMST(vector<Edge*> &);

  private:
    void DFS(int, bool *);

    uint32_t _nVertices = 0;
    // list<AdjPair> *_adj; // adjacency list of vertices, 1D array of list
    // list<int> *_adj; // adjacency list of vertices, 1D array of list
    vector<Edge> _edges;
};

class CycleBreaking
{
  public:
      CycleBreaking() {};
      ~CycleBreaking() {};
      void processing();
      void processingDirected();
      void processingUnirected();
      bool readFile(const char *);
      bool writeFile(const char *);
      void reportGraph() const;
      void KruskalMST();

  private:
    bool _isDirected = false;
    uint32_t _nEdges = 0;
    int _rmWeightSum = 0;
    Graph *_graph;
    vector<Edge*> _removedEdges;
};

#endif // _CYCLEBREAKING_H_