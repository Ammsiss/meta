#include "editor.h"

#include "aggregates.h"

void Editor::addLetter(const Point2d curP, const int input)
{ 
    const std::size_t curY{ static_cast<size_t>(curP.y) };

    m_data[curY].insert(m_data[curY].begin() + curP.x, static_cast<char>(input));
}

void Editor::popLetter(const Point2d curP)
{
    const std::size_t curY{ static_cast<size_t>(curP.y) };

    m_data[curY].erase(m_data[curY].begin() + curP.x - 1);
}

// Adds line below cursor, potentially splits line
void Editor::addLine(const Point2d curP)
{
    if (curP.x == getLineLength(curP.y))
    {
        m_data.insert(m_data.begin() + curP.y + 1, "");
    }
    else
    {
        splitLine(curP);
    }
}

void Editor::splitLine(const Point2d curP)
{
    const std::size_t curY{ static_cast<size_t>(curP.y) };

    std::string subStr{ m_data[curY].substr(static_cast<size_t>(curP.x)) };
    m_data[curY].erase(m_data[curY].begin() + curP.x, m_data[curY].end());
    m_data.insert(m_data.begin() + curP.y + 1, subStr);
}

// Pops current line, potentially merges current line content to previous line
void Editor::popLine(int curY)
{
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



