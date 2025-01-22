#ifndef CURSOR_H
#define CURSOR_H

#include <ncurses.h>

#include "aggregates.h"

class Window;

class Cursor
{
public:
    Cursor() = default;

    Cursor(Point2d cursorPosition)
    : m_cursorPosition { cursorPosition } {}

    void setCursor(Point2d delta, int hOffset = -1)
    {
        m_cursorPosition.y += delta.y;
        m_cursorPosition.x += delta.x;

        if (hOffset != -1)
            m_cursorPosition.x = hOffset;
    }

    Point2d getCursor() const
    {
        return m_cursorPosition;
    }

    void setCachedX(int cachedX)
    {
        m_cachedX = cachedX;
    }

    int getCahcedX() const
    {
        return m_cachedX;
    }
    
private:
    Point2d m_cursorPosition{};
    int m_cachedX{};
};

#endif


