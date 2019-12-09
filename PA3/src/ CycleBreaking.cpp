#include " CycleBreaking.h"

CycleBreaking::CycleBreaking()
{

}

CycleBreaking::~CycleBreaking()
{

}

void CycleBreaking::processing()
{
    
}

bool CycleBreaking::readFile(const char *filename)
{
    ifstream ifs(filename);
    if (!ifs.is_open())
        return false;

    string str = "";
    ifs >> str;
    if (str == "d")
        isDirected = true;

    ifs >> nVertices;
    ifs >> nEdges;

    for (uint32_t i = 0; i < nVertices; ++i)
    {
        int i, j, w;
        ifs >> i >> j >> w;
        // getline(ifs, str, '\n');
    }

    ifs.close();
    return true;
}

bool CycleBreaking::writeFile(const char *filename)
{
    ofstream ofs(filename);
    if (!ofs.is_open())
        return false;

    ofs.close();
    return true;
}