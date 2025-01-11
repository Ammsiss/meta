#include <ncurses.h>

#include <string>

#include "window.h"

Window::Window()
{
    int y{};
    int x{};
    getmaxyx(stdscr, y, x);
    m_win = newwin(y, x - 4, 0, 4);
}

Window::~Window()
{
    delwin(m_win);
}

void Window::updateWindow(int y, int x)
{
    // werase(win); to clear artifacts. (potentially unecessary)
    delwin(m_win);
    m_win = newwin(y, x - 4, 0, 4);
}

int Window::getLineLength(int line)
{
    return static_cast<int>(std::size(m_data[static_cast<size_t>(line)]));
}

WINDOW* Window::getWin() const
{
    return m_win;
}

std::vector<std::string> Window::getData() const
{
    return m_data;
}
void Window::appendData(int line, int ch)
{
    m_data[static_cast<size_t>(line)].push_back(static_cast<char>(ch));
}
void Window::popData(int line)
{
    m_data[static_cast<size_t>(line)].pop_back();
}


void Window::newLine()
{
    m_data.push_back("");
}
void Window::delLine()
{
    m_data.pop_back();
}
