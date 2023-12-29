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

    generateDungeon();
}

DungeonMaker::~DungeonMaker()
{
}

void DungeonMaker::drawDungeon(Draw* d)
{
    //node* prev = parent;
    //std::vector<node*> prevNeighbors = prev->neighbors;
    for(int i = 0; i < sizeX; i ++)
    {
        for(int j = 0; j < sizeY; j ++)
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

void DungeonMaker::generateDungeon()
{
    srand(time(NULL));

    parent->x = rand() % sizeX;
    parent->y = rand() % sizeY;
    map[parent->x][parent->y] = 1;

    node* prev = parent;
    int nodesToMake = numNodes;
    while(nodesToMake > 0)
    {
        std::vector<int> validN;

        // search for valid neighbor among previous node's neighbors
        bool xIsZero = rand() % 2;
        std::vector<int> validX;
        std::vector<int> validY;

        for(int j = -1; j <= 1; j ++){
            if(prev->y + j >= 0 && prev->y + j < sizeY){
                if(map[prev->x][prev->y + j] == 0){
                    validY.push_back(prev->y + j);
                }
            }
            if(prev->x + j >= 0 && prev->x + j < sizeX){
                if(map[prev->x + j][prev->y] == 0){
                    validX.push_back(prev->x + j);
                }
            }
        }

        if((xIsZero && validY.size() > 0) || validX.size() == 0)
            validN = validY;
        else
            validN = validX;

        if(validN.size() > 0)
        {
            // add new node to map
            node* newNode = new node();
            newNode->x = prev->x;
            newNode->y = prev->y;
            //std::cout << "validn: " << validN.size() << std::endl;
            int newN = validN[rand() % validN.size()];
            if((xIsZero && validY.size() > 0) || validX.size() == 0)
                newNode->y = newN;
            else
                newNode->x = newN;

            newNode->neighbors.push_back(prev);
            prev->neighbors.push_back(newNode);
            map[newNode->x][newNode->y] = 1;

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
