#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

#include <string>
#include <vector>

class Window
{
public:
    // Delete copy stuff so no shallow copy
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window()
    {
        int y{};
        int x{};
        getmaxyx(stdscr, y, x);
        m_win = newwin(y, x - 4, 0, 4);
        keypad(m_win, true);
    }

    ~Window() { delwin(m_win); }
    
    void resetWindow(int y, int x)
    {
        delwin(m_win);
        m_win = newwin(y, x - 4, 0, 4);
    }
    WINDOW* getWin() const { return m_win; } // maybe make const

private:
    WINDOW* m_win{};
};

#endif
