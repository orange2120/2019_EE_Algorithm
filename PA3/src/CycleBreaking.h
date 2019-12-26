#ifndef _CYCLEBREAKING_H_
#define _CYCLEBREAKING_H_

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

typedef pair<int, int16_t> AdjPair;
typedef pair<int, AdjPair> VPair;
typedef pair<int, int> EdgePair;

// vertex color
#define WHITE 0
#define GRAY  1
#define BLACK 2

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
    Graph(uint32_t &, uint32_t &, bool);
    ~Graph();
    void addEdge(int &, int &, int16_t &);
    // bool isConnected();
    void printVertices() const;
    void printAllEdges() const;
    void printCycle(vector<int> &) const;
    void printEdge(vector<Edge> &) const;
    void KruskalMST(vector<Edge*> &);

  private:
    inline void cycleBacktrace(vector<AdjPair> &, vector<int>);
    bool DFS(int, int, uint8_t *, vector<AdjPair> &);
    uint32_t _nVertices = 0;
    uint32_t _nEdges = 0;
    bool _directed = false;

    AdjPair cycle_start = make_pair(-1, 0);
    int cycle_end = -1;

    list<AdjPair> *_adj; // adjacency list of vertices, 1D array of list
    // unordered_map<int, AdjPair> _vmap;
    vector<Edge> _edges;
};

class CycleBreaking
{
  public:
    CycleBreaking() {};
    ~CycleBreaking() {};
    void processing();
    bool readFile(const char *);
    bool writeFile(const char *);
    void reportGraph() const;

  private:
    bool _isDirected = false;
    int _rmWeightSum = 0;
    Graph *_graph;
    vector<Edge*> _removedEdges;
};

#endif // _CYCLEBREAKING_H_