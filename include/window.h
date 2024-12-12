#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <vector>

class Window
{
public:
    // Delete copy stuff so no shallow copy
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window();
    Window(int y, int x);
    ~Window();
    
    void updateWindow(int y, int x);
    int getPrevLineLength();
    WINDOW* getWin() const;
    std::string getContent() const;
    void appendContent(char code);
    void popContent();

private:
    WINDOW* win{};
    std::string windowContent{"\n"};

};

#endif
