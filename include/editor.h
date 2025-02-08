#ifndef EDITOR_H
#define EDITOR_H

#include <deque>
#include <string>

#include "aggregates.h"

class Window;
class Input;
class Cursor;

class Editor
{
public:
    // constructors/destructors
    Editor() = default;

    // getters/setters
    int getScrollOffset() const { return m_scrollOffset; }
    void setData(std::deque<std::string> data) { m_data = data; }
    const std::deque<std::string>& getData() const { return m_data; }

    // methods
    void addLetter(const int input);
    void popLetter();
    void addLine();
    void splitLine(const Point2d curP);
    void popLine();

    void moveUp();
    void moveDown();
    void moveLeft(); 
    void moveRight();

    // APPLICATION FUNCTIONS
    void handleCharacter(Input input);
    void handleBackspace();
    void handleDeleteCharacter();
    void handleDeleteLine();
    void handleNewline();

    void renderCursor(const Window& win) const;

private:
    std::deque<std::string> m_data{ "" };
    Point2d m_curP{};
    int m_cachedX{};
    int m_scrollOffset{};

    void setCursorY(const bool relative, const int curY); 
    void setCursorX(const bool relative, const int curX);
    int getLogicalY() const { return m_scrollOffset + m_curP.y; }
    int getLineLength(int line) const;
};

#endif

