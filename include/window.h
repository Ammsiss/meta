#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

#include <string>
#include <deque>

#include "aggregates.h"
#include "cursor.h"
#include "editor.h"
#include "resizeHandle.h"

class Window
{
public:
    // constructors/destructors
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // remove ncurses functions
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

    // getters/setters
    WINDOW* getWin() const { return m_win; }

    Point2d getDimensions() const { return m_dimensions; }
    void setDimensions(Point2d dimensions) { m_dimensions = dimensions; }

    // methods

    void clearWindow()
    {
        wclear(m_win);
    }
    
    void renderContent(const std::deque<std::string>& data)
    {
        wmove(m_win, 0, 0);

        for (std::size_t index{ 0 }; index < data.size(); ++index)
        {
            wprintw(m_win, "%s\n", data[index].c_str());
        }
    }

    void renderCursor(const Cursor& cursor, const Editor& editor)
    {
        wattron(m_win, A_REVERSE);

        Point2d curP{ cursor.getCursor() };
        if (curP.x == editor.getLineLength(curP.y))
        {
            mvwprintw(m_win, curP.y, curP.x, " ");
        }
        else
        {
            mvwprintw(m_win, curP.y, curP.x, "%c", editor.getData()[static_cast<std::size_t>(curP.y)][static_cast<std::size_t>(curP.x)]);
        }

        wattroff(m_win, A_REVERSE);
    }

private:
    WINDOW* m_win{};
    Point2d m_dimensions{};
};

#endif
