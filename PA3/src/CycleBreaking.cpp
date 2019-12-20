#include "CycleBreaking.h"

/**************************************/
/*class CycleBreaking member functions*/
/**************************************/

CycleBreaking::CycleBreaking()
{
}

void CycleBreaking::processing()
{
    if(_isDirected)
        processingDirected();
    else
        processingUnirected();
}

void CycleBreaking::processingDirected()
{
    
}

void CycleBreaking::processingUnirected()
{
    _graph->removeNonDec(_removedEdges);
    for (uint32_t i = 0; i < _removedEdges.size(); ++i)
        _rmWeightSum += _removedEdges[i].weight;
}

bool CycleBreaking::readFile(const char *filename)
{
    ifstream ifs(filename);
    if (!ifs.is_open())
        return false;

    uint32_t nV = 0;
    string str = "";
    ifs >> str;
    if (str == "d")
        _isDirected = true;

    ifs >> nV;
    ifs >> _nEdges;

    _graph = new Graph(nV);

    for (uint32_t k = 0; k < _nEdges; ++k)
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
            ofs << _removedEdges[i].u << " " << _removedEdges[i].v
            << " " << _removedEdges[i].weight << endl;
    }
    
    ofs.close();
    return true;
}

void CycleBreaking::reportGraph() const
{
    cout << "======Vertices======" << endl;
    _graph->printVertices();
    cout << "======Edges======" << endl;
    _graph->printEdges();
}

/**************************************/
/*    class Graph member functions    */
/**************************************/
Graph::Graph(uint32_t &v) : _nVertices(v)
{
    _adj = new list<int>[v];
}

Graph::~Graph()
{
    delete []_adj;
}

// Add edge connecting vertice u and v with weight w
// for undirected graph
void Graph::addEdge(int &u, int &v, int16_t &w)
{
    _adj[u].push_back(v);
    _adj[v].push_back(u);
    Edge e{u, v, w};
    _edges.push_back(e);
}

bool Graph::isConnected()
{
    bool visited[_nVertices] = {false};
    DFS(0, visited);

    for (uint32_t i = 0; i < _nVertices; ++i)
        if(!visited[i])
            return false; // un-reachable
    return true;
}

void Graph::findCycleDFS(int v, int parent, int &cycleN, uint8_t *color, int *vis, int *pars)
{
    // vis[v] = true;
    if (color[v] == 2)
        return;

    if (color[v] == 1)
    {
        cycleN++;
        int curr = parent;
        vis[curr] = cycleN;
        while (curr != v)
        {
            curr = pars[curr];
            vis[curr] = cycleN;
        }
        return;
    }

    pars[v] = parent;
    color[v] = 1;

    for (auto i = _adj[v].begin(); i != _adj[v].end(); ++i)
    {
        if (*i == pars[v])
            continue;
        findCycleDFS(*i, v, cycleN, color, vis, pars);
    }

    color[v] = 2;
    /*
    for (auto i = _adj[v].begin(); i != _adj[v].end(); ++i)
    {
        if (!vis[*i])
        {
            if (isCycleDFS(vis, *i, v, cycleV))
            {
                return true;
            }
        }
        else if (*i != parent)
        {
            cycleV.push_back(*i);
            return true;
        }
    }
    return false;
    */
}

bool Graph::hasCycle()
{
    vector<int> cycleVertices[_nVertices];
    // bool visited[_nVertices] = {false};

    uint8_t color[_nVertices] = {0};
    int parent[_nVertices] = {0};
    int visited[_nVertices] = {0};

    int nCycle = 0;
/*
    for (uint32_t i = 0; i < _nVertices; ++i)
    {
        cerr << visited[i] << " ";
    }
    cerr << endl;
*/
    findCycleDFS(1, 0, nCycle, color, visited, parent);

    cerr << "DFS done." << endl;
/*
    for (uint32_t i = 0; i < _nVertices; ++i)
    {
        cerr << (uint32_t)color[i] << " ";
    }
    cerr << endl;
*/

    for (uint32_t i = 0; i < _edges.size(); ++i)
    {
        cerr << visited[i] << " ";
    }

    for (uint32_t i = 0; i < _edges.size() - 1; ++i)
    {
        if (visited[i] != 0)
            cycleVertices[visited[i]].push_back(i);
    }

    cerr << "NC: " << nCycle << endl;

    for (int32_t i = 0; i < nCycle; ++i)
    {
        printCycle(cycleVertices[i]);
    }

    /*
    for (uint32_t i = 0; i < _nVertices; ++i)
    {
        if (!visited[i])
        {
            if (isCycleDFS(visited, i, -1, cycleVertices))
            {
                printCycle(cycleVertices);
                return true;
            }
        }
    }
    */
    return false;
}

// remove edges in non-decreasing order/
void Graph::removeNonDec(vector<Edge> &de)
{
    // sorting edges in non-decreasing order
    sort(_edges.begin(), _edges.end());

    printEdges();

    hasCycle();

    // delete edge from vertices
    // for (int32_t i = _edges.size() - 1; i >= 0; --i)
    /*
    for (uint32_t i = 0; i < _edges.size(); ++i)
    {
        int u = _edges[i].u;
        int v = _edges[i].v;
        _adj[u].remove(v);
        _adj[v].remove(u);
        de.push_back(_edges[i]);

        cerr << "R (" << u << "," << v << ")" << endl;

        if (!hasCycle())
        {
            cerr << "Has no" << endl;
            _adj[u].push_back(v);
            _adj[v].push_back(u);
            de.pop_back();
            printEdges();
        }

    }
    */
}

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

void Graph::printEdges() const
{
    cout << "Total: " << _edges.size() << endl;
    for (uint32_t i = 0; i < _edges.size(); ++i)
    {
        cout << "[" << i << "] (" <<
        _edges[i].u << "," << _edges[i].v << ")"
        << _edges[i].weight << endl;
    }
}

void Graph::printCycle(vector<int> &cV) const
{
    for (uint32_t i = 0; i < cV.size(); ++i)
        cout << "Cycle: " << cV[i] << "-" << endl;
}

void Graph::DFS(int v, bool *vis)
{
    vis[v] = true;
    for (auto i = _adj[v].begin(); i != _adj[v].end(); ++i)
        if(!vis[*i])
            DFS(*i, vis);
}