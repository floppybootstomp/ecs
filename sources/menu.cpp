#include "../headers/globalVars.h"
#include "../headers/menu.h"

Menu::Menu(int mx, int my, std::vector<std::string> mItems, Draw *dr, int ipc)
{
    x = mx;
    y = my;
    index = 0;
    itemsPerCol = ipc;

    menuItems = mItems;
    menuSize = (int)menuItems.size();

    d = dr;
}

Menu::~Menu()
{
}

void Menu::addMenuItem(std::string item)
{
    menuItems.push_back(item);
    menuSize = (int)menuItems.size();
}

void Menu::drawMenu()
{
    for(int i = 0; i < menuSize; i++)
    {
        if(i == index)
            d->drawString(stdscr, y+((i%6)*2)+1, x + (22*(i/itemsPerCol)), menuItems[i], LIGHT_PALLET);
        else
            d->drawString(stdscr, y+((i%6)*2)+1, x + (22*(i/itemsPerCol)), menuItems[i], BACKGROUND_PALLET);
    }
}

void Menu::menuUp()
{
    if(index > 0)
        index --;
    else
        index = menuSize-1;
}

void Menu::menuDown()
{
    index = (index + 1) % menuSize;
}

std::string Menu::getCurrentEntry()
{
    return menuItems[index];
}
