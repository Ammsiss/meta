#include <ncurses.h>
#include <signal.h>
#include <chrono>

#include <atomic>
#include <sys/ioctl.h>
#include <unistd.h>

#include "resizeHandle.h"
#include "window.h"

void ResizeHandle::setFlag(int sig)
{
    if (sig == SIGWINCH)
    {
        s_resizeFlag.store(true);
    }    
}

void getTerminalSize(int& rows, int& cols)
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

void ResizeHandle::resize(Window& mainW)
{
    if (s_resizeFlag.load())
    {
        int y{};
        int x{};
        getTerminalSize(y, x);
        resizeterm(y, x); 
        mainW.updateWindow(y, x);

        wmove(mainW.getWin(), 0, 0);
        for(const auto& line : mainW.getData())
        {
            wprintw(mainW.getWin(), line.c_str());
        }

        wrefresh(mainW.getWin());
        s_resizeFlag.store(false);
    }
}
