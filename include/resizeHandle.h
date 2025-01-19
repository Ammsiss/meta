#ifndef RESIZE_HANDLE
#define RESIZE_HANDLE

#include <ncurses.h>

#include <sys/ioctl.h>
#include <unistd.h>

#include "aggregates.h"
#include "window.h"

class ResizeHandle
{
public:
    static void resize(Window& win)
    {
        Point2d dimensions{};
        getTerminalSize(dimensions.y, dimensions.x);
    
        if (previousSize.y != dimensions.y || previousSize.x != dimensions.x)
        {
            win.setDimensions(Point2d{ dimensions.y, dimensions.x}); 
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

    static inline Point2d previousSize{};
};

#endif
