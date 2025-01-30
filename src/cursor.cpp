#include "cursor.h"
#include "editor.h"
#include "renderingUtils.h"
#include "resizeHandle.h"

void Cursor::setCursorX(const bool relative, const int curX)
{
    if (relative)
        m_curP.x += curX;
    else
        m_curP.x = curX;
}

void Cursor::setCursorY(const bool relative, const int curY)
{
    if (relative)
        m_curP.y += curY;
    else
        m_curP.y = curY;
}

void Cursor::moveUp(const Editor& editor)
{    
    if (m_scrollOffset != 0 && m_curP.y == 0)
    {
        decrementOffset();

        if (m_cachedX <= editor.getLineLength(getLogicalY()))
            m_curP.x = m_cachedX;
        else
            m_curP.x = editor.getLineLength(getLogicalY());  
    }
    else if (m_curP.y != 0)
    {
        --m_curP.y;

        if (m_cachedX <= editor.getLineLength(getLogicalY()))
            m_curP.x = m_cachedX;
        else
            m_curP.x = editor.getLineLength(getLogicalY());
    }
}

void Cursor::moveDown(const Editor& editor)
{
    int dataStructureSize{ static_cast<int>(editor.getData().size()) - 1};

    if (getLogicalY() != dataStructureSize)
    {
        if (m_curP.y == ResizeHandle::getTermSize().y - 1)
        {
            incrementOffset();

            if (m_cachedX <= editor.getLineLength(getLogicalY()))
                m_curP.x = m_cachedX;
            else
                m_curP.x = editor.getLineLength(getLogicalY()); 
        }
        else
        {
            ++m_curP.y;

            if (m_cachedX <= editor.getLineLength(getLogicalY()))
                m_curP.x = m_cachedX;
            else
                m_curP.x = editor.getLineLength(getLogicalY());
        }
    }
} 

void Cursor::moveLeft()
{
    if (m_curP.x != 0)
    {
        --m_curP.x;
        m_cachedX = m_curP.x;
    }
}

void Cursor::moveRight(const Editor& editor)
{
    if (m_curP.x != editor.getLineLength(getLogicalY()))
    {
        ++m_curP.x;
        m_cachedX = m_curP.x;
    }
}
