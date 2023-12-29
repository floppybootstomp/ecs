#include <vector>
#include "draw.h"

#ifndef DUNGEONMAKER_H
#define DUNGEONMAKER_H

class DungeonMaker
{
    int sizeX, sizeY, numNodes;
    int** map;

    struct node {
        int x, y;
        std::vector<node*> neighbors;
        node() : x(0), y(0) {};
    };

    node* parent = new node();

    bool calcIsXZero(bool favorX, int factor);
    bool findValidNeighbors(bool xIsZero, int x, int y, std::vector<int> & validN);
public:
    DungeonMaker(int sX, int sY, int nNodes);
    ~DungeonMaker();

    void drawDungeon(Draw* d);
    
    void generateDungeon(bool favorX, int favorDirMult);
};

#endif // DUNGEONMAKER_H
