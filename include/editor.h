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
    Editor() = default;

    void updateCursor(const Window& win)
    {
        getyx(win.getWin(), m_cursorPosition.y, m_cursorPosition.x);
    }

    void print(const Window& win)
    {
        addLetter();
        wprintw(win.getWin(), "%c", m_input);
    }

    // data manipulation

    void addLetter()
    {
        m_data[static_cast<size_t>(m_cursorPosition.y)].push_back(m_input);
    }

    void addLine()
    {
        m_data.push_back("");
    }

    void popLetter()
    {
        m_data[static_cast<size_t>(m_cursorPosition.y)].pop_back();
    }

    void popLine()
    {
        m_data.pop_back();
    }

    // getters / setters
    int getInput() const { return m_input; }
    void setInput(const Window& win) { m_input = static_cast<char>(wgetch(win.getWin())); }

    const std::deque<std::string>& getData() const { return m_data; }

    Point2D getCursor() const { return m_cursorPosition; }
    void setCursor(Point2D cursorPosition) { m_cursorPosition = cursorPosition; }

private:
    Point2D m_cursorPosition{};
    char m_input{};
    std::deque<std::string> m_data{""};
};

#endif
