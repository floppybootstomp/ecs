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

    std::string consoleText = "";
    std::string errorText = "";
    std::string typingText = "";

    int mode = 0;
    while(mode != 2)
    {
        // load a dungeon
        if(typingText.size() > 0 && mode == 0){
            //int err = dungeon.loadDungeon("dungeons/" + typingText);
            int err = 1;
            if(err == 1)
                errorText = "Could not load dungeon";
            else
                consoleText = "Loaded Dungeon";
                
        }

        dungeon.drawDungeon(d);

        // menu for managing maps
        for(int i = 0; i < 4; i ++)
        {
            theMenuItems[i].selected = BACKGROUND_PALLET;
        }
        theMenuItems[menuSelector].selected = LIGHT_PALLET;
        d->drawString(stdscr, sz/2, 0, "                                                                       ", BACKGROUND_PALLET);
        d->drawString(stdscr, sz/2, 0, consoleText, HIGHLIGHT_PALLET);
        d->drawString(stdscr, sz/2, 0, errorText, COLOR_PALLET);
        d->drawString(stdscr, sz/2, 0, typingText, BACKGROUND_PALLET);
        d->drawString(stdscr, sz/2+1, 0, "New Map", theMenuItems[0].selected);
        d->drawString(stdscr, sz/2+3, 0, "Save Map", theMenuItems[1].selected);
        d->drawString(stdscr, sz/2+5, 0, "Load Map", theMenuItems[2].selected);
        d->drawString(stdscr, sz/2+7, 0, "Quit", theMenuItems[3].selected);

        ch = wgetch(stdscr);

        switch(mode)
        {
            case 0:
                consoleText = "";
                errorText = "";
                typingText = "";
                int e;
                switch(ch)
                {
                    // move up menu
                    case 'w':
                    case 'a':
                    case 'k':
                    case 37:
                    case 39:
                        if(menuSelector > 0)
                            menuSelector --;
                        else
                            menuSelector = 3;
                        break;
                    // move down menu
                    case 's':
                    case 'd':
                    case 'j':
                    case 38:
                    case 40:
                        menuSelector = (menuSelector + 1) % 4;
                        break;
                    case 10:
                        switch(menuSelector)
                        {
                            case 0:
                                // generate a new dungeon
                                dungeon.resetDungeon();
                                break;
                            case 1:
                                // save current dungeon
                                e = dungeon.saveDungeon();
                                if(e)
                                    errorText = "Could not save dungeon";
                                else
                                    consoleText = "Saved Dungeon";

                                break;
                            case 2:
                                // load dungeon
                                mode = 1;
                                break;
                            case 3:
                                // close
                                mode = 2;
                                break;
                        }
                        break;
                    case 'q':
                        mode = 2;
                        break;
                }
                break;
            case 1:
                if(ch == 10)
                    mode = 0;
                else if(ch == 8)
                    typingText.pop_back();

                typingText += ch;
                break;
        }
        refresh();
    }

    endwin();
    return 0;
}
