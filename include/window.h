#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

#include <string>

#include "aggregates.h"
#include "cursor.h"
#include "resizeHandle.h"


class Window
{
public:

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window()
    {
        Point2d dimensions{};
        getmaxyx(stdscr, dimensions.y, dimensions.x);
        m_dimensions = dimensions;
        m_win = newwin(dimensions.y, dimensions.x, 0, 0);
    }

    Window(Point2d dimensions, Point2d position)
    : m_dimensions { dimensions }
    {
        m_win = newwin(m_dimensions.y, m_dimensions.x, position.y, position.x);
    }

    ~Window() { delwin(m_win); }

    WINDOW* getWin() const { return m_win; }

    void resizeWin(const Point2d dimensions)
    {
        m_dimensions = dimensions;
        wresize(m_win, m_dimensions.y, m_dimensions.x);
    }

    void clearWindow() const
    {
        wclear(m_win);
    }

    void moveCursor(int y, int x) const
    {
        wmove(m_win, y, x);
    }

    void movePrint(int y, int x, const std::string& str) const
    {
        mvwprintw(m_win, y, x, str.c_str());
    }

    void print(const std::string& str) const
    {
        wprintw(m_win, str.c_str());
    }

    void reverseOn() const
    {
        wattron(m_win, A_REVERSE);
    }

    void reverseOff() const
    {
        wattroff(m_win, A_REVERSE);
    }

    void refreshWin() const
    {
        wrefresh(m_win);
    }

private:
    WINDOW* m_win{};
    Point2d m_dimensions{};
};

#endif
