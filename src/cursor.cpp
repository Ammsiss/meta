#include "cursor.h"
#include "editor.h"
#include "renderingUtils.h"
#include "resizeHandle.h"

void Cursor::moveUp(const Editor& editor)
{    
    if (rendering::scrollOffset != 0 && m_curP.y == 0)
    {
        rendering::decrementOffset();

        if (m_cachedX <= editor.getLineLength(m_curP.y + rendering::scrollOffset))
            m_curP.x = m_cachedX;
        else
            m_curP.x = editor.getLineLength(m_curP.y  + rendering::scrollOffset);  
    }
    else if (m_curP.y != 0)
    {
        --m_curP.y;

        if (m_cachedX <= editor.getLineLength(m_curP.y + rendering::scrollOffset))
            m_curP.x = m_cachedX;
        else
            m_curP.x = editor.getLineLength(m_curP.y +  rendering::scrollOffset);
    }
}

void Cursor::moveDown(const Editor& editor)
{
    int dataStructureSize{ static_cast<int>(editor.getData().size()) - 1};

    if (m_curP.y + rendering::scrollOffset != dataStructureSize)
    {
        if (m_curP.y == ResizeHandle::getTermSize().y - 1)
        {
            // returns bool
            rendering::incrementOffset(*this);

            if (m_cachedX <= editor.getLineLength(m_curP.y + rendering::scrollOffset))
                m_curP.x = m_cachedX;
            else
                m_curP.x = editor.getLineLength(m_curP.y + rendering::scrollOffset); 
        }
        else
        {
            ++m_curP.y;

            if (m_cachedX <= editor.getLineLength(m_curP.y + rendering::scrollOffset))
                m_curP.x = m_cachedX;
            else
                m_curP.x = editor.getLineLength(m_curP.y + rendering::scrollOffset);
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
    /*
    if (m_curP.x != editor.getLineLength(m_curP.y + offset))
    */

    if (m_curP.x != editor.getLineLength(m_curP.y + rendering::scrollOffset)) // Scroll offset
    {
        ++m_curP.x;
        m_cachedX = m_curP.x;
    }
}
