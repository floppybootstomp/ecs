#include "globalVars.h"

#ifndef COMPONENT_H
#define COMPONENT_H

struct posComponent
{
    int x;
    int y;
    posComponent() : x(0), y(0) {};
    posComponent(int px, int py) : x(px), y(py) {};
};

struct moveComponent
{
    int xSpeed;
    int ySpeed;
    moveComponent() : xSpeed(0), ySpeed(0) {};
    moveComponent(int sx, int sy) : xSpeed(sx), ySpeed(sy) {};
};

struct drawComponent
{
    char image;
    int color;
    drawComponent() : image(' '), color(LIGHT_PALLET) {};
    drawComponent(char i, int c) : image(i), color(c) {};
};

#endif // COMPONENT_H
