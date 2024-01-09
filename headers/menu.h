#include <string>
#include <vector>
#include "draw.h"

#ifndef MENU_H
#define MENU_H

class Menu{

int x, y, menuSize, itemsPerCol;
Draw* d;

public:
    int index;
    std::vector<std::string> menuItems;

    Menu(int mx, int my, std::vector<std::string> menuItems, Draw* dr, int ipc = 6);
    ~Menu();

    void addMenuItem(std::string item);

    void drawMenu();

    void menuUp();

    void menuDown();

    std::string getCurrentEntry();
};
#endif // MENU_H
