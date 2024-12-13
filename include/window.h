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
    int getLineLength(int line);
    WINDOW* getWin() const;

    std::vector<std::string> getData() const;
    void appendData(int lineNum, char ch);
    void popData(int line);

    void newLine();
    void delLine();

private:
    WINDOW* m_win{};
    std::vector<std::string> m_data{""};
};

#endif
