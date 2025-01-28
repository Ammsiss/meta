#ifndef CURSOR_H
#define CURSOR_H

#include "aggregates.h"

class Editor;

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

    void moveUp(const Editor& editor);
    void moveDown(const Editor& editor);
    void moveLeft(); 
    void moveRight(const Editor& editor);

private:
    Point2d m_curP{};
    int m_cachedX{};
};

#endif


