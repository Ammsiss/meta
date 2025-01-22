#include <ncurses.h>

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

    // init main window
    Window mainW{};

    // init editor
    Editor mainE{};

    // init cursor
    Cursor mainC{ Point2d{ 0, 0 } };

    // render cursor here
    mainW.renderCursor(mainC, mainE);
 
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
                mainE.addLine(mainC);

                mainC.setCursor(Point2d{ 1, 0 }, 0);
                mainC.setCachedX(0);
            }

            // Printable characters
            else if (mainE.getInput() >= 32 && mainE.getInput() <= 126)
            {
                mainE.addLetter(mainC);

                mainC.setCursor(Point2d{ 0, 1 });
                mainC.setCachedX(mainC.getCursor().x);
            }

            // Delete key and backspace
            else if (mainE.getInput() == 8 || mainE.getInput() == 127)
            {
                if (mainC.getCursor().x > 0)
                {
                    mainE.popLetter(mainC);

                    mainC.setCursor(Point2d{ 0, -1 });
                    mainC.setCachedX(mainC.getCursor().x);                    
                }
                else if (mainC.getCursor().y > 0)
                {
                    Point2d curP{ mainC.getCursor() };

                    mainE.popLine(curP.y);
                    
                    mainC.setCursor(Point2d{ -1, 0 }, mainE.getLineLength(curP.y - 1));
                    mainC.setCachedX(mainC.getCursor().x);
                }
            }

            else if (mainE.getInput() == KEY_LEFT)
            {
                if (mainC.getCursor().x != 0)
                {
                    mainC.setCursor(Point2d{ 0, -1 });
                    mainC.setCachedX(mainC.getCursor().x);
                }
            }

            else if (mainE.getInput() == KEY_RIGHT)
            {
                if (mainC.getCursor().x != mainE.getLineLength(mainC.getCursor().y))
                {
                    mainC.setCursor(Point2d{ 0, 1 });
                    mainC.setCachedX(mainC.getCursor().x);
                }
            }

            else if (mainE.getInput() == KEY_UP)
            {
                if (mainC.getCursor().y != 0)
                {
                    if (mainC.getCahcedX() <= mainE.getLineLength(mainC.getCursor().y - 1))
                    {
                        mainC.setCursor(Point2d{ -1, 0 }, mainC.getCahcedX());
                    }
                    else
                    {
                        mainC.setCursor(Point2d{ -1, 0 }, mainE.getLineLength(mainC.getCursor().y - 1));
                    }
                }
            }

            else if (mainE.getInput() == KEY_DOWN)
            {
                if (mainC.getCursor().y != static_cast<int>(mainE.getData().size()) - 1)
                {
                    if (mainC.getCahcedX() <= mainE.getLineLength(mainC.getCursor().y + 1))
                    {
                        mainC.setCursor(Point2d{ 1, 0 }, mainC.getCahcedX());
                    }
                    else
                    {
                        mainC.setCursor(Point2d{ 1, 0 }, mainE.getLineLength(mainC.getCursor().y + 1));
                    }
                }
            }

            mainW.clearWindow(); 
            mainW.renderContent(mainE.getData());
            mainW.renderCursor(mainC, mainE);

            mvwprintw(mainW.getWin(), 15, 15, "%d", mainC.getCahcedX());
            wrefresh(mainW.getWin()); 
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
 
    endwin();
}


// new line resets to 0
// x movement changes the value and typing
