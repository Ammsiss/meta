#include <ncurses.h>

#include <string>

#include "window.h"

Window::Window()
{
    int y{};
    int x{};
    getmaxyx(stdscr, y, x);
    win = newwin(y, x - 4, 0, 4);
}

Window::~Window()
{
    delwin(win);
}

void Window::updateWindow(int y, int x)
{
    // werase(win); to clear artifacts. (potentially unecessary)
    delwin(win);
    win = newwin(y, x - 4, 0, 4);
}

int Window::getPrevLineLength()
{
    int length{ 0 };
    size_t i{ std::size(Window::windowContent) - 1 };
    while(Window::windowContent[i] != '\n')
    {
        ++length;
        --i;
    }

    return length;
}

WINDOW* Window::getWin() const
{
    return win;
}

std::string Window::getContent() const
{
    return windowContent; 
}

void Window::appendContent(char code)
{
    windowContent.push_back(code);
}

void Window::popContent()
{
    windowContent.pop_back();
}

