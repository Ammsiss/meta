#ifndef EDITOR_H
#define EDITOR_H

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

    void setData(std::deque<std::string> data) { m_data = data; }
    const std::deque<std::string>& getData() const { return m_data; }

    // methods

    void addLetter(const Point2d curP, const int input);
    void popLetter(const Point2d curP);
    // Adds line below cursor, potentially splits line
    void addLine(const Point2d curP);
    void splitLine(const Point2d curP);
    // Pops current line, potentially merges current line to previous line
    void popLine(int curY);
    int getLineLength(int line) const;

private:
    std::deque<std::string> m_data{ "" };
};

#endif

