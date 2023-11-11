#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include "../headers/globalVars.h"
#include "../headers/draw.h"
#include <curses.h>

using namespace std;

int main()
{
    initscr();
    setlocale(LC_CTYPE, "");
    noecho();
    cbreak();

    int gridsize = 10;
    int wallsize = 2;
    Draw d;

    clear();

    for(int i = 0; i < gridsize + 2*wallsize; i ++)
    {
        for(int j = 0; j < gridsize + 2*wallsize; j ++)
        {
            if(i < wallsize || i >= gridsize+wallsize || j < wallsize || j >= gridsize+wallsize)
            {
                d.drawString(stdscr, i, j, " ", LIGHT_PALLET);
            }
            else if(i == wallsize)
            {
                d.drawString(stdscr, i, j, " ", DARK_PALLET);
            }
            else
            {
                d.drawString(stdscr, i, j, " ", BACKGROUND_PALLET);
            }
        }
    }
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
        d.drawString(stdscr, y, x, "@", BACKGROUND_PALLET);
        refresh();
    }

    endwin();
    return 0;
}
