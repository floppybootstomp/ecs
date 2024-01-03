#include <iostream>
#include <string>

#ifndef FILEIO_H
#define FILEIO_H

class FileIO {

public:
    FileIO();
    ~FileIO();

    int writeMatrix(int** data, int sizeX, int sizeY, std::string filename);
    int** readMatrix(std::string filename);
};

#endif // FILEIO_H
