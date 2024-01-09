#include "../headers/globalVars.h"
#include "../headers/gameObject.h"

GameObject::GameObject(int gx, int gy)
{
    x = gx;
    y = gy;
}

GameObject::~GameObject()
{
}

void GameObject::draw(Draw* d)
{
    d->drawString(stdscr, y, x, std::string(1, img), LIGHT_PALLET);
}

int GameObject::getX()
{
    return x;
}

int GameObject::getY()
{
    return y;
}
