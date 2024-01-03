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
    curs_set(0);
    noecho();
    cbreak();

    Draw* d = new Draw();
    int sz = 64;
    DungeonMaker dungeon(sz, sz/2, sz*3, 3);

    clear();

    move(20, 20);
    refresh();

    int ch = -1;
    //int x, y = 3;
    int menuSelector = 0;
    struct menuItem{
        int selected;
    };
    menuItem theMenuItems[4] = {{BACKGROUND_PALLET}, {BACKGROUND_PALLET}, {BACKGROUND_PALLET}, {BACKGROUND_PALLET}};
    while(ch != 'q')
    {
        dungeon.drawDungeon(d);

        // menu for managing maps
        for(int i = 0; i < 4; i ++)
        {
            theMenuItems[i].selected = BACKGROUND_PALLET;
        }
        theMenuItems[menuSelector].selected = LIGHT_PALLET;
        d->drawString(stdscr, sz/2+1, 0, "New Map", theMenuItems[0].selected);
        d->drawString(stdscr, sz/2+3, 0, "Save Map", theMenuItems[1].selected);
        d->drawString(stdscr, sz/2+5, 0, "Load Map", theMenuItems[2].selected);
        d->drawString(stdscr, sz/2+7, 0, "Quit", theMenuItems[3].selected);

        ch = wgetch(stdscr);

        int e;
        switch(ch)
        {
            // move up menu
            case 'w':
            case 'a':
            case 'k':
                if(menuSelector > 0)
                    menuSelector --;
                else
                    menuSelector = 3;
                break;
            // move down menu
            case 's':
            case 'd':
            case 'j':
                menuSelector = (menuSelector + 1) % 4;
                break;
            case 10:
                switch(menuSelector)
                {
                    case 0:
                        // generate a new dungeon
                        break;
                    case 1:
                        // save current dungeon
                        e = dungeon.saveDungeon();
                        if(e)
                            d->drawString(stdscr, sz/2, 0, "Could not save dungeon", COLOR_PALLET);
                        else
                            d->drawString(stdscr, sz/2, 0, "Saved Dungeon", HIGHLIGHT_PALLET);

                        break;
                    case 2:
                        break;
                    case 3:
                        // close
                        ch = 'q';
                        break;
                }
        }
        //d->drawString(stdscr, y, x, "@", BACKGROUND_PALLET);
        refresh();
    }

    endwin();
    return 0;
}
