#include <ncurses.h>
#include <signal.h>

#include <vector>
#include <string>
#include <atomic>
#include <thread>
#include <chrono>

#include "resizeHandle.h"
#include "window.h"
#include "editor.h"
#include "aggregates.h"

static void initCurses()
{
    initscr();
    cbreak();
    noecho(); 
    start_color();
    use_default_colors();
    refresh();
    set_escdelay(50);
    ResizeHandle::initialize();
}

int main()
{
    initCurses();

    int y{};
    int x{};
    getmaxyx(stdscr, y, x);
    Window mainW{ Point2D{ y, x - 4 }, Point2D{ 0, 4 } };
    Editor mainE{};
 
    nodelay(mainW.getWin(), true);
    while (true)
    {
        ResizeHandle::resize(mainW);
         
        mainE.setInput(mainW);

        wclear(mainW.getWin());
        mainW.renderContent(mainE.getData());
        mainE.updateCursor(mainW.getWin());
        wrefresh(mainW.getWin());

        if (mainE.getInput() != ERR)
        {
            // newline
            if (mainE.getInput() == 10)
            {
                mainE.addLetter();
                mainE.addLine();
            }

            // Printable characters
            if (mainE.getInput() >= 32 && mainE.getInput() <= 126)
            {
                mainE.addLetter();
            }

            // Delete key and backspace
            if (mainE.getInput() == 8 || mainE.getInput() == 127)
            {
                if (mainE.getCursor().x > 0)
                {
                    mainE.popLetter(); 
                }
                else if (mainE.getCursor().y > 0)
                {
                    mainE.popLine();
                    mainE.popLetter();
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    getch();
    endwin();
}
