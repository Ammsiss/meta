#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>

#include "window.h"
#include "editor.h"

class Input
{
public:
    Input() = default;

    int getInput() const { return m_input; }
    void setInput(const Window& window) { m_input = wgetch(window.getWin()); }

    void handleInput(Editor& editor);

private:
    int m_input{};
};

#endif
