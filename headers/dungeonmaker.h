#include <vector>
#include <string>
#include <map>
#include "draw.h"

#ifndef DUNGEONMAKER_H
#define DUNGEONMAKER_H

class DungeonMaker
{
    int sizeX, sizeY, numNodes, numRooms;
    int** gameMap;
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

    // deletes all nodes in a room, then deletes the room
    void deleteRoom(room* r);

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
    void generateDungeon();

    // loads dungeon matrix to file returns 1 if error
    int loadDungeon(std::string filename);

    // generates a new dungeon
    void resetDungeon();

    // saves dungeon matrix to file returns 1 if error
    int saveDungeon();
};

#endif // DUNGEONMAKER_H
