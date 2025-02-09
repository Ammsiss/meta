#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

#include <string>

#include "aggregates.h"
#include "resizeHandle.h"


class Window
{
public:

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&& win) noexcept
    : m_win { win.m_win }, m_dimensions { win.m_dimensions }, m_position { win.m_position }
    {
        win.m_win = nullptr;
        win.m_dimensions = Point2d{};
        win.m_position = Point2d{};
    }

    Window& operator=(Window&& win) noexcept
    {
        if (this == &win)
            return *this;

        if (m_win)
            delwin(m_win);

        m_win = win.m_win;
        m_dimensions = win.m_dimensions;
        m_position = win.m_position;

        win.m_win = nullptr;
        win.m_dimensions = Point2d{};
        win.m_position = Point2d{};

        return *this;
    }

    Window()
    {
        m_dimensions = ResizeHandle::getTermSize();
        m_win = newwin(m_dimensions.y, m_dimensions.x, m_position.y, m_position.x);
    }

    Window(Point2d dimensions, Point2d position)
    : m_dimensions { dimensions }, m_position { position }
    {
        m_win = newwin(m_dimensions.y, m_dimensions.x, position.y, position.x);
    }

    ~Window() { delwin(m_win); }

    WINDOW* getWin() const { return m_win; }
    Point2d getPos() const { return m_position; }
    Point2d getDimensions() const { return m_dimensions; }

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

    void dimOn() const
    {
        wattron(m_win, A_DIM);
    }

    void dimOff() const
    {
        wattroff(m_win, A_DIM);
    }

    void boldOn() const
    {
        wattron(m_win, A_BOLD);
    }

    void boldOff() const
    {
        wattroff(m_win, A_BOLD);
    }

    void refreshWin() const
    {
        wrefresh(m_win);
    }

private:
    WINDOW* m_win{};
    Point2d m_dimensions{};
    Point2d m_position{};
};

#endif
