#include "../headers/fileio.h"
#include <fstream>

FileIO::FileIO(){
}

FileIO::~FileIO(){
}

int FileIO::writeMatrix(int** data, int sizeX, int sizeY, std::string filename)
{
    std::ofstream f;
    f.open(filename);
    if(!f)
        return 1;

    for(int i = 0; i < sizeY; i ++)
    {
        for(int j = 0; j < sizeX; j ++)
        {
            f << data[i][j] << " ";
        }
        f << "\n";
    }

    f.close();

    return 0;
}
