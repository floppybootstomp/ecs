#include <string>
#include <curses.h>

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
