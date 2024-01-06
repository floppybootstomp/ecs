#include "../headers/fileio.h"
#include <fstream>
#include <sstream>

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

    f << sizeX << " " << sizeY << "\n";

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

int** FileIO::readMatrix(std::string filename)
{
    int* matrixSize = (int*)malloc(2 * sizeof(int));
    int** matrix;
    std::ifstream f;

    f.open(filename.c_str());
    if(!f)
        return 0;

    int a = 0;
    std::string line;
    while(getline(f, line))
    {
        std::istringstream iss(line);
        int n;
        int b = 0;
        if(a == 0)
        {
            while(iss >> n)
            {
                matrixSize[b] = n;
                b ++;
            }

            matrix = (int**)malloc(matrixSize[1] * sizeof(int*));
            for(int i = 0; i < matrixSize[1]; i ++)
            {
                matrix[i] = (int*)malloc(matrixSize[0] * sizeof(int));

                for(int j = 0; j < matrixSize[0]; j ++)
                {
                    matrix[i][j] = 0;
                }
            }
        }
        else
        {
            while(iss >> n)
            {
                matrix[a-1][b] = n;
                b ++;
            }
        }

        a ++;
    }
    f.close();

    return matrix;
}
