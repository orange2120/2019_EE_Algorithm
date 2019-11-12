#include "maxPlanarSubset.h"

MPS::MPS()
{

}

bool MPS::readFile(const char *filename)
{
    ifstream ifs(filename); // input file
    if (!ifs)
    {
        cerr << "[ERROR] Open input file failed!\n";
        return false;
    }

    ifs >> _nChords;

    // create a 2D array
    _inChordMatrix = new bool*[_nChords];
    for (int i = 0; i < _nChords; ++i)
        _inChordMatrix[i] = new bool[_nChords];

    for (int i = 0; i < _nChords; ++i)
    {
        int a, b;
        ifs >> a >> b;
        _inChordMatrix[a][b] = 1;
        _inChordMatrix[b][a] = 1;
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

    ofs << _outChords << endl;

    ofs.close();

    return true;
}

void MPS::process()
{
    _auxMatrix = new int*[_nChords];
    for (int i = 0; i < _nChords; ++i)
        _auxMatrix[i] = new int[_nChords];
    
    for (int i = 0; i < _nChords; ++i)
    {
        for (int l = 0; l < _nChords - 1; ++l)
        {
            for (int k = 0; k < _nChords - l; ++k)
            {
                int j = i + l;
                _auxMatrix[i][j] = _auxMatrix[i][j - 1];
                
            }
        }
    }

}

void MPS::printAdjMatrix()
{
    for (int i = 0; i < _nChords; ++i)
    {
        for (int j = 0; j < _nChords; ++j)
        {
            cout << _inChordMatrix[i][j] << " ";
        }
        cout << endl;
    }
}