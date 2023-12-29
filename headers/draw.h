#include <string>
#include <curses.h>

#ifndef DRAW_H
#define DRAW_H

class Draw
{
public:
    Draw();
    ~Draw();

    // check for colors and initialize
    void initColors();

    // draws a char to the screen
    void drawString(WINDOW *win, int startX, int startY, std::string c, int colorPallet);
};

#endif // DRAW_H
