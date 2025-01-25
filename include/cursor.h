#ifndef CURSOR_H
#define CURSOR_H

#include <ncurses.h>

#include <optional>

#include "aggregates.h"
#include "editor.h"
#include "resizeHandle.h"

class Window;

class Cursor
{
public:
    Cursor() = default;

    Cursor(Point2d curP)
    : m_curP { curP } {}

    void updateCache()
    {
        m_cachedX = m_curP.x;
    }

    void handleUp(const Editor& editor, std::optional<const int> lineLength = std::nullopt)
    {
        if (m_curP.y != 0)
        {
            if (m_cachedX <= editor.getLineLength(m_curP.y - 1))
            {
                --m_curP.y;

                if (lineLength)
                {
                    m_curP.x = *lineLength;
                    m_cachedX = m_curP.x;
                }
                else
                {
                    m_curP.x = m_cachedX;
                }
            }
            else
            {
                --m_curP.y;
                m_curP.x = editor.getLineLength(m_curP.y);
            }
        }
    }

    void handleDown(const Editor& editor)
    {
        // condition needs to change
        if (m_curP.y != static_cast<int>(editor.getData().size()) - 1 && m_curP.y != ResizeHandle::getTermSize().y - 1)
        {
            if (m_cachedX <= editor.getLineLength(m_curP.y + 1))
            {
                ++m_curP.y;
                m_curP.x = m_cachedX;
            }
            else
            {
                ++m_curP.y;
                m_curP.x = editor.getLineLength(m_curP.y);
            }
        }
    }

    void handleLeft()
    {
        if (m_curP.x != 0)
        {
            --m_curP.x;
            m_cachedX = m_curP.x;
        }
    }

    void handleRight(const int lineLength)
    {
        if (m_curP.x != lineLength)
        {
            ++m_curP.x;
            m_cachedX = m_curP.x;
        }
    }

    void setX(int delta)
    {
        m_curP.x = delta;
    }

    void setY(int delta)
    {
        m_curP.y = delta;
    }

    Point2d getCursor() const
    {
        return m_curP;
    }

    void setCachedX(int cachedX)
    {
        m_cachedX = cachedX;
    }

    int getCahcedX() const
    {
        return m_cachedX;
    }

    void updateCursorState()
    {
        m_curState.curP = m_curP;
        m_curState.cachedX = m_cachedX;
    }

    CurState getCursorState() const
    {
        return m_curState;
    }
   
private:
    Point2d m_curP{};
    int m_cachedX{};
    CurState m_curState{};
};

#endif


