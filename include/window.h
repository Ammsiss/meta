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
    : m_dimensions { dimensions }, m_position { position }
    {
        m_win = newwin(m_dimensions.y, m_dimensions.x, m_position.y, m_position.x);
        keypad(m_win, true);
    }

    ~Window() { delwin(m_win); }

    // getters/setters
    WINDOW* getWin() const { return m_win; }
    void setDimensions(Point2D dimensions) { m_dimensions = dimensions; }

    // methods
    void resetWindow()
    {
        delwin(m_win);
        m_win = newwin(m_dimensions.y, m_dimensions.x, m_position.y, m_position.x);
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
    Point2D m_position{};
};

#endif
