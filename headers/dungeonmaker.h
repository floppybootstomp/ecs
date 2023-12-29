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

public:
    DungeonMaker(int sX, int sY, int nNodes);
    ~DungeonMaker();

    void drawDungeon(Draw* d);
    
    void generateDungeon();
};

#endif // DUNGEONMAKER_H
