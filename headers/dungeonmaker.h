#include <vector>
#include <string>
#include "draw.h"

#ifndef DUNGEONMAKER_H
#define DUNGEONMAKER_H

class DungeonMaker
{
    int sizeX, sizeY, numNodes;
    int** map;
    std::string name;

    struct node {
        int x, y;
        std::vector<node*> neighbors;
        node() : x(0), y(0) {};
    };

    struct room {
        int width, height;
        node* parent;
        room(int w, int h) : width(w), height(h), parent(new node()) {};
    };

    std::vector<room*> dungeonRooms;

    // add new node vertically or horizontally
    bool calcIsXZero(bool favorX, int factor);

    // find number of neighbors for node
    int findNumNeighbors(int x, int y);

    // find valid neighbors for node
    bool findValidNeighbors(bool xIsZero, int x, int y, int w, int h, std::vector<int> & validN);

    // generate a room
    node generateRoom(room* rm, int pX, int pY, int roomWidth, int roomHeight, bool favorX, int favorDirMult);

public:
    DungeonMaker(int sX, int sY, int nNodes, int nRooms);
    ~DungeonMaker();

    // draw a dungeon
    void drawDungeon(Draw* d);

    // generate a dungeon
    void generateDungeon(int numRooms);

    // saves dungeon matrix to file returns 1 if error
    int saveDungeon();
};

#endif // DUNGEONMAKER_H
