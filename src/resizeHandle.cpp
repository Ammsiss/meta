#include "resizeHandle.h"

#include <sys/ioctl.h>
#include <unistd.h>

#include "aggregates.h"
#include "window.h"


void ResizeHandle::resizeMain(Window& win)
{
    win.resizeWin(Point2d{ termSize.y, termSize.x - win.getPos().x });
}

void ResizeHandle::resizeSide(Window& win)
{
    win.resizeWin(Point2d{ termSize.y, 4 });
}

bool ResizeHandle::resize()
{
    Point2d term{};
    setTermSize(term.y, term.x);

    if (termSize.y != term.y || termSize.x != term.x)
    {
        termSize = term;
        return true;
    }

    return false;
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

