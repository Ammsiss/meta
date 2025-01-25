#include <ncurses.h>

#include "window.h"

class Input
{
public:
    Input() = default;

    int getInput() const { return m_input; }
    void setInput(const Window& window) { m_input = wgetch(window.getWin()); }

private:
    int m_input{};
};
