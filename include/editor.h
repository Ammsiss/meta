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

        if (curP.x == getLineLength(curP.y))
        {
            m_data[lineNum].push_back(static_cast<char>(m_input));
        } 
        else
        {
            m_data[lineNum].insert(m_data[lineNum].begin() + curP.x, static_cast<char>(m_input));
        }
    }

    void addLine()
    {
        m_data.push_back("");
    }

    void popLetter(const Cursor& cursor)
    {
        const Point2d curP{ cursor.getCursor() };
        const std::size_t lineNum{ static_cast<size_t>(curP.y) };

        m_data[lineNum].erase(m_data[lineNum].begin() + curP.x - 1);
    }

    void popLine()
    {
        m_data.pop_back();
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
