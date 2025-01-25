#include "editor.h"

#include "aggregates.h"

void Editor::addLetter(const Point2d curP)
{ 
    const std::size_t curY{ static_cast<size_t>(curP.y) };

    m_data[curY].insert(m_data[curY].begin() + curP.x, static_cast<char>(m_input));
}

void Editor::popLetter(const Point2d curP)
{
    const std::size_t curY{ static_cast<size_t>(curP.y) };

    m_data[curY].erase(m_data[curY].begin() + curP.x - 1);
}

void Editor::addLine(const Point2d curP)
{
    const size_t curY{ static_cast<size_t>(curP.y) };

    if (curP.x != getLineLength(curP.y))
    {
        std::string subStr{ m_data[curY].substr(static_cast<size_t>(curP.x)) };
        m_data[curY].erase(m_data[curY].begin() + curP.x, m_data[curY].end());
        m_data.insert(m_data.begin() + curP.y + 1, subStr);
    }
    else
    {
        m_data.insert(m_data.begin() + curP.y + 1, "");
    }
}

void Editor::popLine(int curY)
{
    if (getLineLength(curY) != 0)
    {
        std::string str{ m_data[static_cast<size_t>(curY)] };
        m_data.erase(m_data.begin() + curY);
        m_data[static_cast<size_t>(curY) - 1].append(str);
    }
    else
    {
        m_data.erase(m_data.begin() + curY);
    }
}

int Editor::getLineLength(int line) const
{
    return static_cast<int>(std::ssize(m_data[static_cast<size_t>(line)]));
}



