#include <string>
#include "draw.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject{
protected:
    char img;
    int x, y, id;
    std::string name;

public:
    GameObject(int gx, int gy);
    ~GameObject();

    void draw(Draw* d);

    int getX();

    int getY();

    void move(int distance, int direction);
};
#endif // GAMEOBJECT_H
