#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include "../headers/globalVars.h"
#include "../headers/draw.h"
#include "../headers/dungeonmaker.h"
#include "../headers/menu.h"
#include "../headers/entityManager.h"
#include "../headers/component.h"
#include "../headers/system.h"
#include "../headers/entityAttributeManager.h"
#include <curses.h>
#include <dirent.h>

#define MAIN_MODE 0
#define QUIT_MODE 1

int main()
{
    EntityManager e;
    EntityAttributeManager componentManager;
    EntityAttributeManager systemManager;

    e.addEntity();
    e.addEntity();
    e.addEntity();
    e.addEntity();
    e.addEntity();

    for(int i = 0; i <= 4; i ++)
    {
        if(i != 0)
        {
            componentManager.set<moveComponent>(i, new moveComponent(0, 5));
            systemManager.set<moveSystem>(i, new moveSystem());
            componentManager.set<drawComponent>(i, new drawComponent('@', BACKGROUND_PALLET));
        }
        componentManager.set<posComponent>(i, new posComponent(0, i));

        if(i != 1)
        {
            //componentManager.set<posComponent>(i, new posComponent(0, i));
        }
    }

    int entity;

    std::cout << "Living entities: " << std::endl;
    for(int i = 0; i < MAX_ENTITIES; i ++)
    {
        entity = e.getEntity(i);
        if(entity != -1){
            std::cout << entity << ": (" << componentManager.get<posComponent>(entity)->x << ", " << componentManager.get<posComponent>(entity)->y << ")" << std::endl;
        }
    }
    //std::cout << std::endl;

    e.removeEntity(2);
    componentManager.entityDestroyed(2);
    e.removeEntity(3);
    componentManager.entityDestroyed(3);
    e.addEntity();
    systemManager.get<moveSystem>(1)->execute(&componentManager, 1);

    std::cout << "Living entities: " << std::endl;
    for(int i = 0; i < MAX_ENTITIES; i ++)
    {
        entity = e.getEntity(i);
        if(entity != -1){
            std::cout << entity << ": (" << componentManager.get<posComponent>(entity)->x << ", " << componentManager.get<posComponent>(entity)->y << ")" << std::endl;
            e.removeEntity(i);
            componentManager.entityDestroyed(i);
        }
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
