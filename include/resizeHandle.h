#ifndef RESIZE_HANDLE
#define RESIZE_HANDLE

#include <ncurses.h>

#include <atomic>
#include <sys/ioctl.h>
#include <unistd.h>

#include "window.h"
#include "editor.h"

class ResizeHandle
{
public:
    static void resize(Window& win)
    {
        int y{};
        int x{};
        getTerminalSize(y, x);
    
        if (previousSize.y != y || previousSize.x != x)
        {
            win.setDimensions(Point2D{ y, x - 4 }); 
            wresize(win.getWin(), win.getDimensions().y, win.getDimensions().x);
        }
    }
 
    // methods
    static void getTerminalSize(int& rows, int& cols)
    {
        struct winsize ws{};
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) 
        {
            perror("ioctl");
            rows = LINES;
            cols = COLS;
        }
        else
        {
            rows = ws.ws_row;
            cols = ws.ws_col;
        }
    }

    static void initialize()
    {
        getTerminalSize(previousSize.y, previousSize.x);
    }

    static inline Point2D previousSize{};
};

#endif
