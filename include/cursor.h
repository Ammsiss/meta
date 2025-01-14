#ifndef CURSOR_H
#define CURSOR_H

#include <ncurses.h>

#include "aggregates.h"
#include "window.h"

class Cursor
{
public:
    Cursor(Point2D cursorPosition)
    : m_cursorPosition { cursorPosition } {}

    void setCursor(Point2D delta, int hOffset = -1)
    {
        m_cursorPosition.y += delta.y;
        m_cursorPosition.x += delta.x;

        if (hOffset != -1)
            m_cursorPosition.x = hOffset;
    }

    Point2D getCursor() const
    {
        return m_cursorPosition;
    }

    void printCursor(const Window& win) const
    {
        mvwprintw(win.getWin(), m_cursorPosition.y, m_cursorPosition.x, "%c", m_cursor);
    }
    
private:
    Point2D m_cursorPosition{};
    char m_cursor{ '|' };
};

#endif
