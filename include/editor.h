#ifndef EDITOR_H
#define EDITOR_H

#include <ncurses.h>

#include <vector>
#include <deque>
#include <string>

#include "cursor.h"

class Editor
{
public:
    // constructors/destructors
    Editor() = default;

    // getters/setters
    int getInput() const { return m_input; }
    void setInput(int input) { m_input = input; }

    const std::deque<std::string>& getData() const { return m_data; }

    // methods

    void addLetter(const Cursor& cursor)
    { 
        const Point2d curP{ cursor.getCursor() };
        const std::size_t lineNum{ static_cast<size_t>(curP.y) };

        m_data[lineNum].insert(m_data[lineNum].begin() + curP.x, static_cast<char>(m_input));

    }

    void popLetter(const Cursor& cursor)
    {
        const Point2d curP{ cursor.getCursor() };
        const std::size_t lineNum{ static_cast<size_t>(curP.y) };

        m_data[lineNum].erase(m_data[lineNum].begin() + curP.x - 1);
    }

    void addLine(const Cursor& cursor)
    {
        const Point2d curP{ cursor.getCursor() };
        const size_t lineNum{ static_cast<size_t>(curP.y) };

        if (curP.x != getLineLength(curP.y))
        {
            std::string subStr{ m_data[lineNum].substr(static_cast<size_t>(curP.x)) };
            m_data[lineNum].erase(m_data[lineNum].begin() + curP.x, m_data[lineNum].end());
            m_data.insert(m_data.begin() + cursor.getCursor().y + 1, subStr);
        }
        else
        {
            m_data.insert(m_data.begin() + cursor.getCursor().y + 1, "");
        }
    }

    void popLine(int curY, int curX)
    {
        if (curX != getLineLength(curY))
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

    int getLineLength(int line) const
    {
        return static_cast<int>(std::ssize(m_data[static_cast<size_t>(line)])); 
    }


private:
    int m_input{};
    std::deque<std::string> m_data{""};
};

#endif

