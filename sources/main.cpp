#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include "../headers/globalVars.h"
#include "../headers/draw.h"
#include "../headers/dungeonmaker.h"
#include <curses.h>

using namespace std;

int main()
{
    initscr();
    setlocale(LC_CTYPE, "");
    noecho();
    cbreak();

    Draw* d = new Draw();
    DungeonMaker dungeon(4, 32, 32);

    clear();

    dungeon.drawDungeon(d);
    move(20, 20);
    refresh();

    int ch = -1;
    int x, y = 3;
    while(ch != 'q')
    {
        ch = wgetch(stdscr);

        switch(ch)
        {
            case 'w':
                y --;
                break;
            case 'a':
                x --;
                break;
            case 's':
                y ++;
                break;
            case 'd':
                x ++;
                break;
        }
        d->drawString(stdscr, y, x, "@", BACKGROUND_PALLET);
        refresh();
    }

    endwin();
    return 0;
}
