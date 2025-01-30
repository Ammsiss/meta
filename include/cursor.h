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
    int getScrollOffset() const { return m_scrollOffset; }
    int getLogicalY() const { return m_scrollOffset + m_curP.y; }
    void incrementOffset() { ++m_scrollOffset; }
    void decrementOffset() { --m_scrollOffset; }

    void setCursorY(const bool relative, const int curY); 
    void setCursorX(const bool relative, const int curX);

    void moveUp(const Editor& editor);
    void moveDown(const Editor& editor);
    void moveLeft(); 
    void moveRight(const Editor& editor);

private:
    Point2d m_curP{};
    int m_cachedX{};
    int m_scrollOffset{};
};

#endif


