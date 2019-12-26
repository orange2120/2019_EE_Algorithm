#include "CycleBreaking.h"

/**************************************/
/*class CycleBreaking member functions*/
/**************************************/
void CycleBreaking::processing()
{
    if(_isDirected)
    {
        dirFindCycle();
    }
    else
    {
        _graph->KruskalMST(_removedEdges);

        for (uint32_t i = 0; i < _removedEdges.size(); ++i)
        _rmWeightSum += _removedEdges[i]->weight;
    }
}

bool CycleBreaking::readFile(const char *filename)
{
    ifstream ifs(filename);
    if (!ifs.is_open())
        return false;

    uint32_t nV = 0, nE = 0;
    char type;
    ifs >> type;
    if (type == 'd')
        _isDirected = true;
   
    ifs >> nV;
    ifs >> nE;

    _graph = new Graph(nV, nE, _isDirected); // build the graph

    for (uint32_t k = 0; k < nE; ++k)
    {
        int i, j;
        int16_t w;
        ifs >> i >> j >> w;
        // cout << i << " " << j << " " << w << endl;
        _graph->addEdge(i, j, w);
    }

    ifs.close();
    return true;
}

bool CycleBreaking::writeFile(const char *filename)
{
    ofstream ofs(filename);
    if (!ofs.is_open())
        return false;
    
    if(_removedEdges.empty())
        ofs << "0" << endl;
    else
    {
        ofs << _rmWeightSum << endl;
        for (uint32_t i = 0; i < _removedEdges.size(); ++i)
            ofs << _removedEdges[i]->u << " " << _removedEdges[i]->v
            << " " << _removedEdges[i]->weight << endl;
    }

    delete _graph;

    ofs.close();
    return true;
}

void CycleBreaking::reportGraph() const
{
    cout << "======Vertices======" << endl;
    // _graph->printVertices();
    cout << "======Edges======" << endl;
    _graph->printAllEdges();
}

/**************************************/
/*    class Graph member functions    */
/**************************************/
Graph::Graph(uint32_t &nv, uint32_t &ne, bool dir) : _nVertices(nv), _nEdges(ne), _directed(dir)
{
    if (_directed)
        _adj = new list<AdjPair>[v];
        // _adj = new list<int>[nv];
    _edges.reserve(ne);
}

Graph::~Graph()
{
    if (_directed)
        delete[] _adj;
}

// Add edge connecting vertice u and v with weight w
// for undirected graph
void Graph::addEdge(int &u, int &v, int16_t &w)
{
    if (_directed)
    {
        _adj[u].push_back(make_pair(v, w));
    }
    Edge e{u, v, w};
    _edges.push_back(e);
}

// remove edges in non-decreasing order/
void Graph::KruskalMST(vector<Edge*> &rmEdges)
{
    DisjoinSet set(_nVertices); // create the disjoin set

    sort(_edges.begin(), _edges.end());

    for (int32_t i = _edges.size() - 1; i >= 0; --i)
    {
        if (set.find(_edges[i].u) != set.find(_edges[i].v))
            set.Union(_edges[i].u, _edges[i].v);
        else
            rmEdges.push_back(&_edges[i]);
    }
}

void Graph::dirFindCycle(vector<Edge*> &rmEdges)
{

    while (1)
    {
        uint8_t color[_nVertices] = {0};
        vector<AdjPair> parents;
        vector<Edge> cycleE;
        // find cycle
        for (uint32_t v = 0; v < _nVertices; ++v)
        {
            if (color[v] == WHITE && DFS(v, -1, color, visited, parents))
                break;
        }
        if (cycle_start == -1)
            break;

        cycleBacktrace(parents, cycleV);
        printEdge(cycleE);
    }
}

inline void Graph::cycleBacktrace(vector<AdjPair> &parents, vector<Edge> &cycleE)
{
    // Edge start{cycle_start, }
    // cycleE.push_back();
    for (int v = cycle_end; v != cycle_start; v = parents[v])
    {


    }
}

// u: current vertex
bool Graph::DFS(int u, int p, uint8_t *color, vector<AdjPair> &parents)
{
    color[u] = GRAY;
    vis[u] = true;
    parents[u] = p;

    for (auto i = _adj[u].begin(); i != _adj[u].end(); ++i)
    {
        int v = (*i).first;
        if (color[v] == GRAY)
        { 
            // found a Cycle
            cycle_start = make_pair(v, *i);
            cycle_end = u;
            return true;
        }
        else if (color[v] == WHITE)
        {
            DFS(v, u, color, vis, parents);
            return true;
        }
    }

    color[v] = BLACK;
    return false;
}

void Graph::printAllEdges() const
{
    cout << "Total: " << _edges.size() << endl;
    for (uint32_t i = 0; i < _edges.size(); ++i)
    {
        cout << "[" << i << "] (" <<
        _edges[i].u << "," << _edges[i].v << ")-"
        << _edges[i].weight << endl;
    }
}


void Graph::printEdge(vector<Edge> &e) const
{
    for (uint32_t i = 0; i < e.size(); ++i)
        cout << e[i].u << "-(" << e[i].weight << ")-" << e[i].v << endl;
}

void Graph::printCycle(vector<int> &cV) const
{
    for (uint32_t i = 0; i < cV.size(); ++i)
        cout << "Cycle: " << cV[i] << "-" << endl;
}

/*
bool Graph::isConnected()
{
    bool visited[_nVertices] = {false};
    DFS(0, visited);

    for (uint32_t i = 0; i < _nVertices; ++i)
        if(!visited[i])
            return false; // un-reachable
    return true;
}
*/


/**************************************/
/*  class DisjoinSet member functions */
/**************************************/
DisjoinSet::DisjoinSet(uint32_t &n) : _nSubset(n)
{
    _subs = new subset[n];
    makeSet();
}

DisjoinSet::~DisjoinSet()
{
    delete[] _subs;
}

void DisjoinSet::makeSet()
{
    for (uint32_t i = 0; i < _nSubset; ++i)
    {
        _subs[i].parent = i;
        _subs[i].rank = 0;
    }
}

int DisjoinSet::find(int &i) const
{
    if (_subs[i].parent == i)
        return i;
    else
        return find(_subs[i].parent);
}

void DisjoinSet::Union(int &i, int &j)
{
    int iRoot = find(i);
    int jRoot = find(j);
    if (_subs[iRoot].rank < _subs[jRoot].rank)
        _subs[iRoot].parent = jRoot;
    else if (_subs[iRoot].rank > _subs[jRoot].rank)
        _subs[jRoot].parent = iRoot;
    else
    {
        _subs[jRoot].parent = iRoot;
        _subs[iRoot].rank++;
    }
}

/*
void Graph::printVertices() const
{
    cout << "Total: " << _nVertices << endl;
    for (uint32_t i = 0; i < _nVertices; ++i)
    {
        cout << "[" << i << "]";
        for (auto j = _adj[i].begin(); j != _adj[i].end(); ++j)
            cout << "->" << *j;
        cout << endl;
    }
}
*/


/*
void Graph::DFS(int v, bool *vis)
{
    vis[v] = true;
    for (auto i = _adj[v].begin(); i != _adj[v].end(); ++i)
        if(!vis[*i])
            DFS(*i, vis);
}
*/

/*
template <T>
void countingSort()
{

*/
