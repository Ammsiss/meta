#include "editor.h"

#include "editor.h"
#include "renderingUtils.h"
#include "resizeHandle.h"
#include "input.h"

#include "aggregates.h"

void Editor::addLetter(const int input)
{ 
    const std::size_t curY{ static_cast<size_t>(getLogicalY()) };

    m_data[curY].insert(m_data[curY].begin() + m_curP.x, static_cast<char>(input));
}

void Editor::popLetter()
{
    const std::size_t curY{ static_cast<size_t>(getLogicalY()) };

    m_data[curY].erase(m_data[curY].begin() + m_curP.x - 1);
}

void Editor::addLine()
{
    int curY{ getLogicalY() };

    if (m_curP.x == getLineLength(curY))
    {
        m_data.insert(m_data.begin() + curY + 1, "");
    }
    else
    {
        const std::size_t ucurY{ static_cast<size_t>(curY) };

        std::string subStr{ m_data[ucurY].substr(static_cast<size_t>(m_curP.x)) };
        m_data[ucurY].erase(m_data[ucurY].begin() + m_curP.x, m_data[ucurY].end());
        m_data.insert(m_data.begin() + curY + 1, subStr);
    }
}

void Editor::popLine()
{
    int curY{ getLogicalY() };

    if (getLineLength(curY) == 0)
    {
        m_data.erase(m_data.begin() + curY);
    }
    else
    {
        const std::size_t ucurY{ static_cast<std::size_t>(curY) };

        std::string str{ m_data[ucurY] };
        m_data.erase(m_data.begin() + curY);
        m_data[ucurY - 1].append(str);
    }
}

int Editor::getLineLength(int line) const
{
    return static_cast<int>(std::ssize(m_data[static_cast<size_t>(line)]));
}

// CURSOR FUNCTIONS

void Editor::setCursorX(const bool relative, const int curX)
{
    if (relative)
        m_curP.x += curX;
    else
        m_curP.x = curX;
}

void Editor::setCursorY(const bool relative, const int curY)
{
    if (relative)
        m_curP.y += curY;
    else
        m_curP.y = curY;
}

void Editor::moveUp()
{    
    if (m_scrollOffset != 0 && m_curP.y == 0)
    {
        --m_scrollOffset;

        if (m_cachedX <= getLineLength(getLogicalY()))
            m_curP.x = m_cachedX;
        else
            m_curP.x = getLineLength(getLogicalY());  
    }
    else if (m_curP.y != 0)
    {
        --m_curP.y;

        if (m_cachedX <= getLineLength(getLogicalY()))
            m_curP.x = m_cachedX;
        else
            m_curP.x = getLineLength(getLogicalY());
    }
}

void Editor::moveDown()
{
    int dataStructureSize{ static_cast<int>(m_data.size()) - 1};

    if (getLogicalY() != dataStructureSize)
    {
        if (m_curP.y == ResizeHandle::getTermSize().y - 1)
        {
            ++m_scrollOffset;

            if (m_cachedX <= getLineLength(getLogicalY()))
                m_curP.x = m_cachedX;
            else
                m_curP.x = getLineLength(getLogicalY()); 
        }
        else
        {
            ++m_curP.y;

            if (m_cachedX <= getLineLength(getLogicalY()))
                m_curP.x = m_cachedX;
            else
                m_curP.x = getLineLength(getLogicalY());
        }
    }
} 

void Editor::moveLeft()
{
    if (m_curP.x != 0)
    {
        --m_curP.x;
        m_cachedX = m_curP.x;
    }
}

void Editor::moveRight()
{
    if (m_curP.x != getLineLength(getLogicalY()))
    {
        ++m_curP.x;
        m_cachedX = m_curP.x;
    }
}

// APPLICATION FUNCTIONS

void Editor::handleCharacter(Input input)
{
    bool cursorNotAtEnd{ m_curP.x != ResizeHandle::getTermSize().x - 5 };
    bool lineNotFull{ getLineLength(getLogicalY()) != ResizeHandle::getTermSize().x - 5 };

    if (cursorNotAtEnd && lineNotFull)
    {
        // editor relies on cursor state
        addLetter(input.getInput());

        setCursorX(true, 1);
        m_cachedX = m_curP.x;
    }
}

void Editor::handleBackspace()
{
    if (m_curP.x > 0)
    {
        handleDeleteCharacter();
    }
    else if (m_scrollOffset != 0 || m_curP.y != 0)
    {
        handleDeleteLine();
    }
}

void Editor::handleDeleteCharacter()
{
    // editor relies on cursor state
    popLetter();

    setCursorX(true, -1);
    m_cachedX = m_curP.x;
}

void Editor::handleDeleteLine()
{
    const int lineLength{ getLineLength(getLogicalY() - 1) };
    
    if (m_curP.y != 0)
    {
        // editor relies on cursor state
        popLine(); 

        setCursorY(true, -1);
        setCursorX(false, lineLength);
        m_cachedX = m_curP.x;
    }
    else
    {
        popLine();

        --m_scrollOffset;
        setCursorX(false, lineLength);
        m_cachedX = m_curP.x;
    }
}

void Editor::handleNewline()
{ 
    // editor relies on cursor state
    addLine();

    if (m_curP.y == ResizeHandle::getTermSize().y - 1)
        ++m_scrollOffset;
    else
        setCursorY(true, 1);

    setCursorX(false, 0);
    m_cachedX = m_curP.x;
}

void Editor::renderCursor(const Window& window) const
{
    window.reverseOn();

    if (m_curP.x == getLineLength(m_curP.y + m_scrollOffset))
    {
        window.movePrint(m_curP.y, m_curP.x, " ");
    }
    else
    {
        std::size_t logicalY{ static_cast<std::size_t>(getLogicalY()) };
        std::size_t curX{ static_cast<std::size_t>(m_curP.x) };
        std::string charToPrint{ m_data[logicalY][curX] };

        window.movePrint(m_curP.y, m_curP.x, charToPrint);
    }

    window.reverseOff();
}
