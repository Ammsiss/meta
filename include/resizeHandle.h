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

    static void resize(Window& win)
    {
        if (s_resizeFlag.load())
        {
            int y{};
            int x{};
            getTerminalSize(y, x);
            resizeterm(y, x);
            win.setDimensions(Point2D{ y, x });
            win.resetWindow();

            s_resizeFlag.store(false);
        }
    }

private:
    // variables
    static inline std::atomic<bool> s_resizeFlag{ false };

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
};

#endif
