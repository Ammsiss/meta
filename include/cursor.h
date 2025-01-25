#ifndef CURSOR_H
#define CURSOR_H

#include <ncurses.h>

#include "aggregates.h"
#include "editor.h"

class Window;

class Cursor
{
public:
    // sets cached x to cursor x
    void updateCache() { m_cachedX = m_curP.x; }
    Point2d getCursor() const { return m_curP; }

    void setCursorY(const bool relative, const int curY)
    {
        if (relative)
            m_curP.y += curY;
        else
            m_curP.y = curY;
    }
    
    void setCursorX(const bool relative, const int curX)
    {
        if (relative)
            m_curP.x += curX;
        else
            m_curP.x = curX;
    }

    // Future: Consider extracting common logic for updating m_curP.x
    // if movement beyond arrow keys (e.g., shortcuts) is added.
    void moveUp(const Editor& editor)
    {
        if (m_curP.y != 0)
        {
            --m_curP.y;

            if (m_cachedX <= editor.getLineLength(m_curP.y))
                m_curP.x = m_cachedX;
            else
                m_curP.x = editor.getLineLength(m_curP.y);
        }
    }

    void moveDown(const Editor& editor)
    {
        int dataStructureSize{ static_cast<int>(editor.getData().size()) };

        if (m_curP.y != dataStructureSize - 1)
        {
            ++m_curP.y;

            if (m_cachedX <= editor.getLineLength(m_curP.y))
                m_curP.x = m_cachedX;
            else
                m_curP.x = editor.getLineLength(m_curP.y);
        }
    } 

    void moveLeft()
    {
        if (m_curP.x != 0)
        {
            --m_curP.x;
            m_cachedX = m_curP.x;
        }
    }

    void moveRight(const Editor& editor)
    {
        if (m_curP.x != editor.getLineLength(m_curP.y))
        {
            ++m_curP.x;
            m_cachedX = m_curP.x;
        }
    }

private:
    Point2d m_curP{};
    int m_cachedX{};
};

#endif


