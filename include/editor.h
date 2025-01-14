#ifndef EDITOR_H
#define EDITOR_H

#include <ncurses.h>

#include <vector>
#include <deque>
#include <string>

#include "aggregates.h"
#include "window.h"

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

    void addLetter()
    {
        m_data.back().push_back(static_cast<char>(m_input));
    }

    void addLine()
    {
        m_data.push_back("");
    }

    void popLetter()
    {
        m_data.back().pop_back();
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
    int m_lineNum{};
};

#endif
