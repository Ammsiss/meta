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
#include "cursor.h"
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
    curs_set(0);
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
    Cursor mainC{ Point2D{ 0, 0 } };
    mainC.printCursor(mainW);
 
    nodelay(mainW.getWin(), true);
    while (true)
    {
        ResizeHandle::resize(mainW);

        mainE.setInput(wgetch(mainW.getWin()));
        if (mainE.getInput() != ERR)
        {
            // newline
            if (mainE.getInput() == 10)
            {
                // Data structure editing
                mainE.addLetter();
                mainE.addLine();

                // cursor editing
                mainC.setCursor(Point2D{ 1, 0 }, 0);
            }

            // Printable characters
            if (mainE.getInput() >= 32 && mainE.getInput() <= 126)
            {
                // data structure editing
                mainE.addLetter();

                // cursor editing
                mainC.setCursor(Point2D{ 0, 1 });
            }

            // Delete key and backspace
            if (mainE.getInput() == 8 || mainE.getInput() == 127)
            {
                if (mainC.getCursor().x > 0)
                {
                    mainE.popLetter();
                    mainC.setCursor(Point2D{ 0, -1 });
                }
                else if (mainC.getCursor().y > 0)
                {
                    mainE.popLine();
                    mainE.popLetter();
                    mainC.setCursor(Point2D{ -1, 0 }, mainE.getLineLength(mainC.getCursor().y - 1));
                }
            }            

            mainW.clearWindow(); 
            mainW.renderContent(mainE.getData());
            mainC.printCursor(mainW);
            wrefresh(mainW.getWin()); 
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
 
    endwin();
}
