#ifndef EDITOR_H
#define EDITOR_H

#include <ncurses.h>

#include <deque>
#include <string>

#include "aggregates.h"

class Cursor;

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

    void addLetter(const Point2d curP);
    void popLetter(const Point2d curP);
    void addLine(const Point2d curP);
    void popLine(int curY);
    int getLineLength(int line) const;

private:
    int m_input{};
    std::deque<std::string> m_data{ "" };
};

#endif

