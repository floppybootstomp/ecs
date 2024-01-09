#include "../headers/globalVars.h"
#include "../headers/player.h"

Player::Player(int px, int py) : GameObject(px, py)
{
    id = 4;
    img = '@';
    color = LIGHT_PALLET;
}

Player::~Player()
{
}

void Player::move(int distance, int direction){
    switch(direction)
    {
        case UP:
            if(y - distance >= 0)
                y -= distance;
            break;
    }
}
