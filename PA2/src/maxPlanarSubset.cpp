#include "maxPlanarSubset.h"
#include <iomanip>
#include <algorithm>
#include <vector>

MPS::MPS()
{

}

MPS::~MPS()
{
    for (int i = 0; i < _nVertices; ++i)
    {
        delete[] _inChordMatrix[i];
        _inChordMatrix[i] = NULL;
    }
    delete[] _inChordMatrix;
    _inChordMatrix = NULL;

    for (int i = 0; i < _nVertices; ++i)
    {
        delete[] _auxMatrix[i];
        _auxMatrix[i] = NULL;
    }
    delete[] _auxMatrix;
    _auxMatrix = NULL;

    delete[] _testChord;
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

    // create a 2D array
    _inChordMatrix = new bool*[_nVertices];
    for (int i = 0; i < _nVertices; ++i)
        _inChordMatrix[i] = new bool[_nVertices];

    _testChord = new int[_nVertices];

    // build adjacency matrix of chords
    for (int i = 0; i < _nVertices / 2; ++i)
    {
        int a, b;
        ifs >> a >> b;
        _inChordMatrix[a][b] = 1;
        _inChordMatrix[b][a] = 1;
        _testChord[b] = a;
        _testChord[a] = b;
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

    _maxChords = _auxMatrix[0][_nVertices - 1];
    
    ofs << _maxChords << endl;

    vector<pair<int, int>> outArr;
    outArr.reserve(_nVertices);

    for (int i = 0; i < _nVertices; ++i)
    {
        if (_auxMatrix[0][i] != 0)
        {
            if (_auxMatrix[0][i] > _auxMatrix[0][i - 1])
            {
                outArr.push_back(make_pair(_testChord[i], i));
            }
        }
    }

    sort(outArr.begin(), outArr.end());

    for (int i = 0; i < outArr.size(); ++i)
    {
        ofs << outArr[i].first << " " << outArr[i].second << endl;
    }

    /*
    for (int i = 0; i < _nVertices; ++i)
    {
        for (int j = i; j < _nVertices; ++j)
        {
            if (_auxMatrix[i][j] == 1)
            {
                ofs << i << " " << j << endl;
                break;
            }
        }
    }
    */

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

    // initialize diagonal = 0
    for (int i = 0; i < _nVertices; ++i)
    {
        _auxMatrix[i][i] = 0;
    }
    
    for (int j = 0; j < _nVertices; ++j)
    {
        for (int i = 0; i < j; ++i)
        {
            // search k from j
            int k = _testChord[j];
            // case 1
            _auxMatrix[i][j] = _auxMatrix[i][j - 1];
            
            if (k >= j || k < i)
                continue;
            /*
            for (int m = i; m < j; ++m)
            {
                
                if (_inChordMatrix[k][j])
                {
                    cout << "k = " << k << endl;
                    k = m;
                    break;
                }
            }
            */

            if (_auxMatrix[i][k - 1] + _auxMatrix[k + 1][j - 1] + 1 > _auxMatrix[i][j - 1])
            {
                // cout << "(i,j,k) = " << i << "," << j << "," << k << endl;
                _auxMatrix[i][j] = _auxMatrix[i][k - 1] + _auxMatrix[k + 1][j - 1] + int(_inChordMatrix[k][j]);
            }
            
        }
    }
    /*
    for (int i = 0; i < _nVertices; ++i)
    {
        for (int k = 0; i < j; ++i)
        {
            int k = i;
            // case 1
            _auxMatrix[i][j] = _auxMatrix[i][j - 1];

            // if (_inChordMatrix[k][j])
            if (_inChordMatrix[k][j] && _auxMatrix[i][k - 1] + _auxMatrix[k + 1][j - 1] + 1 > _auxMatrix[i][j - 1])
            {
                // cout << "(i,j,k) = " << i << "," << j << "," << k << endl;
                _auxMatrix[i][j] = _auxMatrix[i][k - 1] + _auxMatrix[k + 1][j - 1] + int(_inChordMatrix[k][j]);
            }
        }
    }
    */
}

void MPS::printAdjMatrix()
{
    if (_inChordMatrix == NULL)
        return;

    cout << "    ";
    for (int i = 0; i < _nVertices; ++i)
        cout << i << " ";
    cout << endl;
    for (int i = 0; i < _nVertices; ++i)
        cout << "---";
    cout << endl;

    cout << "==========Adj==========" << endl;
    for (int i = 0; i < _nVertices; ++i)
    {
        cout << right << setw(2) << i << "| ";
        for (int j = 0; j < _nVertices; ++j)
        {
            cout << _inChordMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void MPS::printAuxMatrix()
{
    if (_auxMatrix == NULL)
        return;
    cout << "==========Aux==========" << endl;
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
            cout << _auxMatrix[i][j] << " ";
        }
        cout << endl;
    }
}