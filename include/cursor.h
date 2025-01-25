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

    Point2d getCursor() const { return m_curP; }

    // sets cached x to cursor x
    void updateCache() { m_cachedX = m_curP.x; }

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

private:
    Point2d m_curP{};
    int m_cachedX{};
};

#endif


