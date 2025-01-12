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
    static void setFlag(int sig)
    {
        if (sig == SIGWINCH)
            s_resizeFlag.store(true);
    }

    static void resize(Window& mainW, const Editor& editor)
    {
        if (s_resizeFlag.load())
        {
            int y{};
            int x{};
            getTerminalSize(y, x);
            resizeterm(y, x); 
            mainW.resetWindow(y, x);

            wmove(mainW.getWin(), 0, 0);

            // SHOULD NOT BE HERE
            for(const auto& line : editor.getData())
            {
                wprintw(mainW.getWin(), line.c_str());
            }

            wrefresh(mainW.getWin());
            s_resizeFlag.store(false);
        }
    }

private:
    // private variables
    static inline std::atomic<bool> s_resizeFlag{ false };

    // private methods
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
};

#endif
