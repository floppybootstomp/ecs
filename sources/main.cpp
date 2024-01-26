#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include "../headers/globalVars.h"
#include "../headers/draw.h"
#include "../headers/dungeonmaker.h"
#include "../headers/menu.h"
#include "../headers/entityManager.h"
#include "../headers/component.h"
#include "../headers/componentManager.h"
#include <curses.h>
#include <dirent.h>

#define MAIN_MODE 0
#define QUIT_MODE 1

int main()
{
    EntityManager e;
    ComponentManager cpm;

    ComponentArray<posComponent> posCA;
    ComponentArray<moveComponent> moveCA;
    ComponentArray<drawComponent> drawCA;

    e.addEntity();
    e.addEntity();
    e.addEntity();
    e.addEntity();
    e.addEntity();

    /*
    cpm.addComponentArray<posComponent>();
    cpm.addComponentArray<moveComponent>();
    cpm.addComponentArray<drawComponent>();
    */

    for(int i = 0; i <= 4; i ++)
    {
        if(i != 0)
        {
            cpm.setComponent<moveComponent>(i, new moveComponent(0, 5));
            cpm.setComponent<drawComponent>(i, new drawComponent('@', BACKGROUND_PALLET));
        }

        if(i != 1)
        {
            cpm.setComponent<posComponent>(i, new posComponent(0, i));
        }
    }

    for(int i = 1; i <= 4; i ++)
    {
        cpm.removeComponent<moveComponent>(i);
        cpm.removeComponent<posComponent>(i);
    }

    /*
    posCA.addComponent(0, new posComponent());
    posCA.addComponent(2, new posComponent());
    posCA.addComponent(3, new posComponent());
    posCA.addComponent(4, new posComponent());
    moveCA.addComponent(1, new moveComponent());
    moveCA.addComponent(2, new moveComponent());
    moveCA.addComponent(3, new moveComponent());
    moveCA.addComponent(4, new moveComponent());
    drawCA.addComponent(1, new drawComponent());
    drawCA.addComponent(2, new drawComponent());
    drawCA.addComponent(3, new drawComponent());
    drawCA.addComponent(4, new drawComponent());
    */

    int entity;

    std::cout << "Living entities: ";
    for(int i = 0; i < MAX_ENTITIES; i ++)
    {
        entity = e.getEntity(i);
        if(entity != -1){
            std::cout << e.getEntity(i) << ", ";
        }
    }
    std::cout << std::endl;

    e.removeEntity(2);
    e.removeEntity(3);
    e.addEntity();

    std::cout << "Living entities: ";
    for(int i = 0; i < MAX_ENTITIES; i ++)
    {
        entity = e.getEntity(i);
        if(entity != -1)
            std::cout << e.getEntity(i) << ", ";
    }
    std::cout << std::endl;
    /*
    initscr();
    setlocale(LC_CTYPE, "");
    curs_set(0);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    Draw* d = new Draw();

    clear();

    move(20, 20);
    refresh();

    std::string consoleText = "";
    std::string errorText = "";

    int ch;
    int mode = MAIN_MODE;
    int sz = 64;

    while(mode != QUIT_MODE)
    {
        // console and error prompts
        d->drawString(stdscr, sz/2, 0, consoleText, HIGHLIGHT_PALLET);
        d->drawString(stdscr, sz/2, 0, errorText, COLOR_PALLET);

        // get user input
        ch = wgetch(stdscr);

        // reset console text
        if(consoleText.size() > 0 || errorText.size() > 0)
        {
            consoleText = "";
            errorText = "";
            clear();
        }

        switch(ch)
        {
            case 'q':
                mode = QUIT_MODE;
                break;
        }
        consoleText = ch;

        refresh();
    }

    delete d;

    endwin();
    
    */
    return 0;
}
