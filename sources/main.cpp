#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include "../headers/draw.h"
#include <curses.h>

using namespace std;

int main()
{
    initscr();
    setlocale(LC_CTYPE, "");

    int gridsize = 10;
    int wallsize = 2;

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    clear();

    for(int i = 0; i < gridsize + 2*wallsize; i ++)
    {
        for(int j = 0; j < gridsize + 2*wallsize; j ++)
        {
            if(i < wallsize || i >= gridsize+wallsize || j < wallsize || j >= gridsize+wallsize)
            {
                attron(COLOR_PAIR(1));
            }
            else
            {
                attron(COLOR_PAIR(2));
            }
            mvaddch(i, j, ' ');
        }
    }
    move(20, 20);
    refresh();
    getch();
    endwin();
    return 0;
}
