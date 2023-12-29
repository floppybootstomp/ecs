#include "../headers/dungeonmaker.h"
#include "../headers/globalVars.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

DungeonMaker::DungeonMaker(int sX, int sY, int nNodes)
{
    sizeX = sX;
    sizeY = sY;
    numNodes = nNodes;
    map = (int**)malloc(sizeY * sizeof(int*));
    for(int i = 0; i < sizeY; i ++)
    {
        map[i] = (int*)malloc(sizeX * sizeof(int));

        for(int j = 0; j < sizeX; j ++)
        {
            map[i][j] = 0;
        }
    }

    generateDungeon(true, 6);
}

DungeonMaker::~DungeonMaker()
{
}

void DungeonMaker::drawDungeon(Draw* d)
{
    //node* prev = parent;
    //std::vector<node*> prevNeighbors = prev->neighbors;
    for(int i = 0; i < sizeY; i ++)
    {
        for(int j = 0; j < sizeX; j ++)
        {
            if(map[i][j] == 1)
            {
                d->drawString(stdscr, i, j, " ", LIGHT_PALLET);
            }
            else
            {
                d->drawString(stdscr, i, j, " ", BACKGROUND_PALLET);
            }
        }
    }
}

// calculates if X is zero and returns whether it is or not
bool DungeonMaker::calcIsXZero(bool favorX, int factor)
{
    int roll = rand() % factor;
    bool isXZero = !favorX ^ (roll > 0);

    return isXZero;
}

// sets validN and returns if the validN is for X
bool DungeonMaker::findValidNeighbors(bool xIsZero, int x, int y, std::vector<int> & validN)
{
    // search for valid neighbor among previous node's neighbors
    std::vector<int> validX;
    std::vector<int> validY;
    bool xIsVN;

    for(int j = -1; j <= 1; j ++){
        if(y + j >= 0 && y + j < sizeY){
            if(map[y + j][x] == 0){
                validY.push_back(y + j);
            }
        }
        if(x + j >= 0 && x + j < sizeX){
            if(map[y][x + j] == 0){
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

void DungeonMaker::generateDungeon(bool favorX, int favorDirMult)
{
    srand(time(NULL));

    parent->x = rand() % sizeX;
    parent->y = rand() % sizeY;
    map[parent->y][parent->x] = 1;

    node* prev = parent;
    int nodesToMake = numNodes;
    while(nodesToMake > 0)
    {
        std::vector<int> validN;
        bool xIsZero = calcIsXZero(!favorX, favorDirMult);
        bool xIsVN = findValidNeighbors(xIsZero, prev->x, prev->y, validN);

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
            map[newNode->y][newNode->x] = 1;

            // next iteration...
            nodesToMake --;
            prev = newNode;
        }
        else
        {
            // if prev has 4 neighbors already, check one of the neighbors
            prev = prev->neighbors[rand() % prev->neighbors.size()];
        }
    }
}
