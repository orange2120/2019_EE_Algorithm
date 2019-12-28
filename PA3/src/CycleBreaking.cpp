#include "CycleBreaking.h"

/**************************************/
/*class CycleBreaking member functions*/
/**************************************/
void CycleBreaking::processing()
{
    if(_isDirected)
    {
        _graph->MFAbyDFS(_removedEdges);
        // _graph->dirFindCycle(_removedEdges);
    }
    else
    {
        _graph->KruskalMST(_removedEdges);
    }
    for (uint32_t i = 0; i < _removedEdges.size(); ++i)
        _rmWeightSum += _removedEdges[i]->weight;
    // cout << "Total Rm E: " << _removedEdges.size() << endl;
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
            << " " << _removedEdges[i]->weight << "\n";
    }

    ofs.flush();
    ofs.close();

    delete _graph;
    return true;
}

void CycleBreaking::reportGraph() const
{
    cout << "======Vertices======" << endl;
    _graph->printVertices();
    cout << "======Edges======" << endl;
    _graph->printAllEdges();
}

/**************************************/
/*    class Graph member functions    */
/**************************************/
Graph::Graph(uint32_t nv, uint32_t ne, bool dir) : _nVertices(nv), _nEdges(ne), _directed(dir)
{
    if (_directed)
        _adj = new list<AdjPair>[nv];
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
        _adj[u].push_back(make_pair(v, w));

    _edges.push_back(Edge{u, v, w});
}

// remove edges in non-decreasing order
void Graph::KruskalMST(vector<Edge *> & rmEdges)
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

void Graph::dirFindCycle(vector<Edge *> &rmEdges)
{
    vector<AdjPair> parents(_nVertices);

    for (uint32_t v = 0; v < _nVertices; ++v)
    {
        bool inCycle[_nVertices] = {false};
        bool addedEdges[_nEdges] = {false};
        uint8_t color[_nVertices] = {0};

        DFS(make_pair(v, 0), -1, color, inCycle, parents, rmEdges, addedEdges);
    }
}

// ap.first = current vertex, ap.second = weight between parent and self
void Graph::DFS(const AdjPair &ap, int p, uint8_t *color, bool *inCycle, vector<AdjPair> &parents, vector<Edge *> &rmEdges, bool *addedEdges)
{
    int u = ap.first; // current vertex
    color[u] = GRAY;

    parents[u] = make_pair(p, ap.second);
    cerr << "[" << p << "] -> [" << u << "] " << ap.second << endl;

    for (auto i = _adj[u].begin(); i != _adj[u].end(); ++i)
    {
        int v = (*i).first;

        for (uint32_t i = 0; i < _nVertices; ++i)
            cerr << (int)color[i] << " ";
        cerr << endl;
        cerr << "(p, curr, next) = " << p << " -> " << u << ", " << v << endl;
        
        if (inCycle[v])
        {
            continue;
        }
        
        // TODO: exclude the edges ever in cycle
        if (color[v] == GRAY)
        {
            // found a Cycle
            dirRemoveE(v, u, (*i).second, inCycle, parents, rmEdges, addedEdges);
            parents.clear();
        }
        else if (color[v] == WHITE)
            DFS(*i, u, color, inCycle, parents, rmEdges, addedEdges);
    }

    color[u] = BLACK;
}

void Graph::dirRemoveE(int &cycle_start, int &cycle_end, int16_t &last_weight, bool *inCycle, vector<AdjPair> &parents, vector<Edge *> &rmEdges, bool *addedEdges)
{
    vector<Edge> cycleE;
    Edge end_e{cycle_end, cycle_start, last_weight};
    Edge min_e{0, 0, INT16_MAX};

    // backtrace edges in the cycle
    inCycle[cycle_end] = inCycle[cycle_start] = true;

    cycleE.push_back(end_e);
    for (int v = cycle_end; v != cycle_start; v = parents[v].first)
    {
        inCycle[v] = true;
        Edge e{parents[v].first, v, parents[v].second};
        cycleE.push_back(e);
    }

    // find minimum weight in edge list
    for (uint32_t i = 0; i < cycleE.size(); ++i)
    {
        if (cycleE[i] < min_e)
            min_e = cycleE[i];
    }

    // printEdge(cycleE);
    cout << "\nrmE = " << min_e.u << "-(" << min_e.weight << ")-" << min_e.v << "\n" << endl;

    // find minimum edge in edge list
    for (uint32_t i = 0; i < _edges.size(); ++i)
    {
        if (_edges[i] == min_e && !addedEdges[i])
        {
            rmEdges.push_back(&_edges[i]);
            addedEdges[i] = true;
        }
    }

    for (uint32_t i = 0; i < _nVertices; ++i)
        cout << (int)inCycle[i] << " ";
    cout << endl;
}

void Graph::printAllEdges() const
{
    cout << "\nTotal: " << _edges.size() << endl;
    for (uint32_t i = 0; i < _edges.size(); ++i)
    {
        cout << "[" << i << "] (" <<
        _edges[i].u << "," << _edges[i].v << ")W "
        << _edges[i].weight << endl;
    }
}

void Graph::printEdge(vector<Edge> &e) const
{
    cout << "\nEdges: " << endl;
    for (uint32_t i = 0; i < e.size(); ++i)
        cout << "[" << e[i].u << "]-(" << e[i].weight << ")-[" << e[i].v << "]" << endl;
}

void Graph::printVertices() const
{
    cout << "\nTotal: " << _nVertices << endl;
    for (uint32_t i = 0; i < _nVertices; ++i)
    {
        cout << "[" << i << "]";
        for (auto j = _adj[i].begin(); j != _adj[i].end(); ++j)
            cout << "->" << (*j).first;
        cout << endl;
    }
}

void Graph::MFAbyDFS(vector<Edge *> &rmEdges)
{
    vector<Edge *> tmpRmE;
    KruskalMST(tmpRmE);

    // remove edges in adjacency list from original graph
    for (uint32_t i = 0; i < tmpRmE.size(); ++i)
    {
        Edge e = *tmpRmE[i];
        list<AdjPair>::iterator it = std::find(_adj[e.u].begin(), _adj[e.u].end(), make_pair(e.v, e.weight));
        _adj[e.u].erase(it);
    }

    // add edges back to the graph and check if there exists a cycle
    for (uint32_t i = 0; i < tmpRmE.size(); ++i)
    {
        if ((*tmpRmE[i]).weight <= 0) // only remove negative weight edges
        {
            rmEdges.push_back(tmpRmE[i]);
            continue;
        }

        _adj[(*tmpRmE[i]).u].push_back(make_pair((*tmpRmE[i]).v, (*tmpRmE[i]).weight));
        if (hasCycle())
        {
            _adj[(*tmpRmE[i]).u].pop_back();
            rmEdges.push_back(tmpRmE[i]);
        }
    }
}

bool Graph::hasCycle() const
{
    uint8_t color[_nVertices] = {WHITE};
    for (int v = 0; v < int(_nVertices); ++v)
    {
        if(color[v] == WHITE)
        {
            if (hasCycleDFS(v, color))
                return true;
        }
    }
    return false;
}

bool Graph::hasCycleDFS(int &u, uint8_t *color) const
{
    color[u] = GRAY;
    /*
    for (uint32_t i = 0; i < _nVertices; ++i)
        cout << (int)color[i] << " ";
    cout << endl;
    */
    for (auto i = _adj[u].begin(); i != _adj[u].end(); ++i)
    {
        int v = (*i).first;
        if (color[v] == GRAY)
            return true;
        else if (color[v] == WHITE && hasCycleDFS(v, color))
            return true;
    }
    color[u] = BLACK;
    return false;
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
