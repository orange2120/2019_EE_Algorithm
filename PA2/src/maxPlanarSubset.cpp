#include "maxPlanarSubset.h"
#include <iomanip>

MPS::MPS()
{

}

MPS::~MPS()
{
    for (int i = 0; i < _nVertices; ++i)
        delete[] _auxMatrix[i];
    delete[] _auxMatrix;

    delete[] _chordTable;
    delete[] _maxChordTable;
}

bool MPS::readFile(const char *filename)
{
    ifstream ifs(filename); // input file
    if (!ifs)
    {
        cerr << "[ERROR] Open input file failed!\n";
        return false;
    }

    ifs >> _nVertices;

    _chordTable = new int[_nVertices];
    _maxChordTable = new bool[_nVertices];

    // build adjacency matrix of chords
    for (int i = 0; i < _nVertices / 2; ++i)
    {
        int a, b;
        ifs >> a >> b;
        _chordTable[b] = a;
        _chordTable[a] = b;
    }

    ifs.close();
    return true;
}

bool MPS::writeFile(const char *filename)
{
    ofstream ofs(filename);
    if (!ofs)
    {
        cerr << "[ERROR] Open output file failed!\n";
        return false;
    }
    
    // number of maximum chords is stored in MIS(0, 2n - 1)
    ofs << _auxMatrix[0][_nVertices - 1] << endl;

    backtrack(0, _nVertices - 1);
   
    for (int i = 0; i < _nVertices; ++i)
    {
        if (_maxChordTable[i])
            ofs << i << " " << _chordTable[i] << endl;
    }

    ofs.close();
    return true;
}

void MPS::process()
{
    _auxMatrix = new int*[_nVertices];
    for (int i = 0; i < _nVertices; ++i)
        _auxMatrix[i] = new int[_nVertices];

    // initialize 
    for (int i = 0; i < _nVertices; ++i)
    {
        for (int j = 0; j < _nVertices; ++j)
            _auxMatrix[i][j] = 0;
    }

    for (int j = 0; j < _nVertices; ++j)
    {
        for (int i = 0; i < j; ++i)
        {
            // get k from j
            int k = _chordTable[j];
            // case 1
            _auxMatrix[i][j] = _auxMatrix[i][j - 1];
            
            if (k >= j || k < i)
                continue;

            // case 2 and case 3
            if (_auxMatrix[i][k - 1] + _auxMatrix[k + 1][j - 1] + 1 > _auxMatrix[i][j - 1])
            {
                // cout << "(i,j,k) = " << i << "," << j << "," << k << endl;
                _auxMatrix[i][j] = _auxMatrix[i][k - 1] + _auxMatrix[k + 1][j - 1] + 1; //int(_inChordMatrix[k][j]);
            }
            
        }
    }
}

void MPS::backtrack(int i, int j)
{
    int k = _chordTable[j];
    if (i < j)
    {
        // case 1
        if ((k >= j && k < i) || (_auxMatrix[i][j] == _auxMatrix[i][j - 1]))
        {
            backtrack(i, j - 1);
        }
        // case 2
        else if (k >= i && k < j)
        {
            _maxChordTable[k] = 1;
            backtrack(i, k - 1);     // case 2-1
            backtrack(k + 1, j - 1); // case 2-2
        }
        // case 3
        else if (k == i)
        {
            _maxChordTable[i] = 1;
            backtrack(i + 1, j - 1);
        }
    }
}

void MPS::printAdjMatrix() const
{
    bool **inChords = new bool*[_nVertices];
    for (int i = 0; i < _nVertices; ++i)
        inChords[i] = new bool[_nVertices];

    for (int i = 0; i < _nVertices; ++i)
        for (int j = 0; j < _nVertices; ++j)
            inChords[i][j] = 0;

    for (int i = 0; i < _nVertices; ++i)
        for (int j = 0; j < _nVertices; ++j)
            if (_chordTable[i] == j)
                inChords[i][j] = 1;

    cout << "==========Adj==========" << endl;
    cout << "    ";
    for (int i = 0; i < _nVertices; ++i)
        cout << i << " ";
    cout << endl;
    for (int i = 0; i < _nVertices; ++i)
        cout << "---";
    cout << endl;
    
    for (int i = 0; i < _nVertices; ++i)
    {
        cout << right << setw(2) << i << "| ";
        for (int j = 0; j < _nVertices; ++j)
        {
            cout << inChords[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < _nVertices; ++i)
        delete[] inChords[i];
    delete[] inChords;
}

void MPS::printAuxMatrix() const
{
    if (_auxMatrix == NULL)
        return;
    cout << "==========Aux==========" << endl;
    cout << "    ";
    for (int i = 0; i < _nVertices; ++i)
        cout << left << setw(2) << i << " ";
    cout << endl;
    for (int i = 0; i < _nVertices; ++i)
        cout << "---";
    cout << endl;

    for (int i = 0; i < _nVertices; ++i)
    {
        cout << right << setw(2) << i << "| ";
        for (int j = 0; j < _nVertices; ++j)
        {
            cout << left << setw(2) <<  _auxMatrix[i][j] << " ";
        }
        cout << endl;
    }
}