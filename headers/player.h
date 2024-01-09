#include "gameObject.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameObject
{
    int color;

public:
    Player(int px, int py);
    ~Player();

    void drawPlayer(Draw* d);

    void move(int distance, int direction);
};
#endif
