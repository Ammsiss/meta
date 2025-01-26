#include "resizeHandle.h"

#include <sys/ioctl.h>
#include <unistd.h>

#include "aggregates.h"
#include "window.h"

void ResizeHandle::resize(Window& win)
{
    Point2d dimensions{};
    setTermSize(dimensions.y, dimensions.x);

    if (termSize.y != dimensions.y || termSize.x != dimensions.x)
    {
        win.resizeWin(dimensions);        
        termSize = dimensions;
    }
}

// methods
void ResizeHandle::setTermSize(int& rows, int& cols)
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

void ResizeHandle::initialize()
{
    setTermSize(termSize.y, termSize.x);
}

Point2d ResizeHandle::getTermSize()
{
    return termSize;
}

