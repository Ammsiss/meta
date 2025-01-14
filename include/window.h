#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

#include <string>
#include <deque>

#include "aggregates.h"

class Window
{
public:
    // constructors/destructors
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Point2D dimensions, Point2D position)
    : m_dimensions { dimensions }
    {
        m_win = newwin(m_dimensions.y, m_dimensions.x, position.y, position.x);
        keypad(m_win, true);
    }

    ~Window() { delwin(m_win); }

    // getters/setters
    WINDOW* getWin() const { return m_win; }

    Point2D getDimensions() const { return m_dimensions; }
    void setDimensions(Point2D dimensions) { m_dimensions = dimensions; }

    // methods

    void clearWindow()
    {
        wclear(m_win);
    }

    void renderContent(const std::deque<std::string>& data)
    {
        wmove(m_win, 0, 0);

        for(const auto& line : data)
        {
            wprintw(m_win, line.c_str());
        }
    }

private:
    WINDOW* m_win{};
    Point2D m_dimensions{};
};

#endif
