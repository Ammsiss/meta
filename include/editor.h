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
    void setInput(const Window& win) { m_input = static_cast<char>(wgetch(win.getWin())); }

    Point2D getCursor() const { return m_cursorPosition; }
    void setCursor(Point2D cursorPosition) { m_cursorPosition = cursorPosition; }

    const std::deque<std::string>& getData() const { return m_data; }

    // methods
    void updateCursor(WINDOW* win)
    {
        getyx(win, m_cursorPosition.y, m_cursorPosition.x);
    }

    void addLetter()
    {
        m_data.back().push_back(m_input);
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

private:
    Point2D m_cursorPosition{};
    char m_input{};
    std::deque<std::string> m_data{""};
};

#endif
