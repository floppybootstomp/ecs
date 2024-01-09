#include "../headers/dungeonmaker.h"
#include "../headers/globalVars.h"
#include "../headers/fileio.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

DungeonMaker::DungeonMaker(int sX, int sY, int nNodes, int nRooms)
{
    srand(time(NULL));

    name = "Dungeon" + std::to_string(rand());
    sizeX = sX;
    sizeY = sY;
    numNodes = nNodes;
    numRooms = nRooms;
    gameMap = (int**)malloc(sizeY * sizeof(int*));
    for(int i = 0; i < sizeY; i ++)
    {
        gameMap[i] = (int*)malloc(sizeX * sizeof(int));

        for(int j = 0; j < sizeX; j ++)
        {
            gameMap[i][j] = 0;
        }
    }

    generateDungeon();
}

DungeonMaker::~DungeonMaker()
{
    for(int i = 0; i < numRooms; i ++)
        deleteRoom(dungeonRooms[i]);

    for(int i = 0; i < sizeY; i ++)
        delete gameMap[i];

    delete gameMap;
}

// add a new dungeon object
void DungeonMaker::addDungeonObject(GameObject* g)
{
    int gId = (int)dungeonObjects.size() + 2;

    dungeonObjects[gId] = g;
    gameMap[g->getY()][g->getX()] = gId;
}

// calculates if X is zero and returns whether it is or not
bool DungeonMaker::calcIsXZero(bool favorX, int factor)
{
    int roll = rand() % factor;
    bool isXZero = !favorX ^ (roll > 0);

    return isXZero;
}

// deletes all nodes in a room, then deletes the room
void DungeonMaker::deleteRoom(room* r)
{
    while(r->parent->neighbors.size() != 0)
    {
        node* p = r->parent;
        node* temp = r->parent;
        while(temp->neighbors.size() > 0 && p != temp->neighbors.back())
        {
            p = temp;
            temp = temp->neighbors.back();
        }
        p->neighbors.pop_back();
        delete temp;
    }
    delete r->parent;
    delete r;
}

void DungeonMaker::drawDungeon(Draw* d)
{
    //node* prev = parent;
    //std::vector<node*> prevNeighbors = prev->neighbors;
    for(int i = 0; i < sizeY; i ++)
    {
        for(int j = 0; j < sizeX; j ++)
        {
            switch(gameMap[i][j])
            {
                case 0:
                    d->drawString(stdscr, i, j, " ", BACKGROUND_PALLET);
                    break;
                case 1:
                    d->drawString(stdscr, i, j, " ", LIGHT_PALLET);
                    break;
                default:
                    dungeonObjects[gameMap[i][j]]->draw(d);
                    break;
            }
        }
    }
}

int DungeonMaker::findNumNeighbors(int x, int y)
{
    int count = 0;
    for(int i = -1; i <= 1; i ++)
        for(int j = -1; j <= 1; j ++)
            if(!(y + i < 0 || y + i >= sizeY) && !(x + j < 0 || x + j >= sizeX) && !(i == j) && !(i == -1*j) && (gameMap[y + i][x + j] == 0))
                count ++;

    return count;
}

// sets validN and returns if the validN is for X
bool DungeonMaker::findValidNeighbors(bool xIsZero, int x, int y, int w, int h, std::vector<int> & validN)
{
    // search for valid neighbor among previous node's neighbors
    std::vector<int> validX;
    std::vector<int> validY;
    bool xIsVN;

    for(int j = -1; j <= 1; j ++)
    {
        if(y + j >= 0 && y + j < h && y + j < sizeY){
            if(gameMap[y + j][x] == 0){
                validY.push_back(y + j);
            }
        }
        if(x + j >= 0 && x + j < w && x + j < sizeX){
            if(gameMap[y][x + j] == 0){
                validX.push_back(x + j);
            }
        }
    }

    xIsVN = (xIsZero && validY.size() > 0) || validX.size() == 0;
    if(xIsVN)
        validN = validY;
    else
        validN = validX;

    return xIsVN;
}

void DungeonMaker::generateDungeon()
{
    node tail;
    bool favorX;
    int roomWidth, roomHeight, roomX, roomY, hNeighbors, tNeighbors, favorDirMult;

    // initialize values for first room
    roomWidth = sizeX/numRooms;
    roomHeight = sizeY/numRooms;
    roomX = rand() % roomWidth;
    roomY = rand() % roomHeight;

    for(int i = 0; i < numRooms; i++)
    {
        favorX = rand() % 2;
        favorDirMult = rand() % 10 + 1;

        // add a new room
        dungeonRooms.push_back(new room(roomWidth, roomHeight));

        // generate a the new room
        tail = generateRoom(dungeonRooms.back(), roomX, roomY, roomWidth, roomHeight, favorX, favorDirMult);

        // find the number of neighbors and choose the greatest to add the next room
        hNeighbors = findNumNeighbors(dungeonRooms.back()->parent->x, dungeonRooms.back()->parent->y);
        tNeighbors = findNumNeighbors(tail.x, tail.y);

        if(hNeighbors > tNeighbors)
        {
            roomX = dungeonRooms.back()->parent->x;
            roomY = dungeonRooms.back()->parent->y;
        }
        else
        {
            roomX = tail.x;
            roomY = tail.y;
        }
    }
}

DungeonMaker::node DungeonMaker::generateRoom(room* rm, int pX, int pY, int roomWidth, int roomHeight, bool favorX, int favorDirMult)
{    
    rm->parent->x = pX;
    rm->parent->y = pY;

    node* prev = rm->parent;
    gameMap[prev->y][prev->x] = 1;
    int nodesToMake = numNodes/5;

    // to terminate the loop if there is a loop in the neighbor map
    int ttl = nodesToMake * 2;
    while(nodesToMake > 0 && ttl > 0)
    {
        std::vector<int> validN;
        bool xIsZero = calcIsXZero(!favorX, favorDirMult);
        bool xIsVN = findValidNeighbors(xIsZero, prev->x, prev->y, prev->x+roomWidth, prev->y+roomHeight, validN);

        if(validN.size() > 0)
        {
            // add new node to map
            node* newNode = new node();
            newNode->x = prev->x;
            newNode->y = prev->y;
            int newN = validN[rand() % validN.size()];
            if(xIsVN)
                newNode->y = newN;
            else
                newNode->x = newN;

            newNode->neighbors.push_back(prev);
            prev->neighbors.push_back(newNode);
            gameMap[newNode->y][newNode->x] = 1;

            // next iteration...
            nodesToMake --;
            prev = newNode;
        }
        else
        {
            if(prev->neighbors.size() == 0)
                return *prev;

            // if prev has 4 neighbors already, check one of the neighbors
            prev = prev->neighbors[rand() % prev->neighbors.size()];
        }

        ttl --;
    }

    return *prev;
}
int DungeonMaker::loadDungeon(std::string filename)
{
    FileIO* fio = new FileIO();
    int ** temp = fio->readMatrix(filename);
    //std::cout << filename << std::endl;
    if(temp == 0)
        return 1;
    else
        gameMap = temp;

    return 0;
}

void DungeonMaker::resetDungeon()
{
    for(int i = 0; i < numRooms; i ++)
    {
        deleteRoom(dungeonRooms[i]);
        dungeonRooms.pop_back();
    }

    for(int i = 0; i < sizeY; i ++)
    {
        for(int j = 0; j < sizeX; j ++)
        {
            gameMap[i][j] = 0;
        }
    }

    name = "Dungeon" + std::to_string(rand());
    generateDungeon();
}

int DungeonMaker::saveDungeon()
{
    FileIO* fio = new FileIO();
    int err = fio->writeMatrix(gameMap, sizeX, sizeY, "dungeons/" + name + ".dgn");
    if(err)
        return 1;

    return 0;
}
