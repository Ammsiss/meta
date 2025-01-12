#include <ncurses.h>
#include <signal.h>

#include <vector>
#include <string>
#include <atomic>

#include "resizeHandle.h"
#include "window.h"
#include "editor.h"

static void initCurses()
{
    initscr();
    cbreak();
    noecho(); 
    start_color();
    use_default_colors();
    refresh();
    set_escdelay(50);
    signal(SIGWINCH, ResizeHandle::setFlag);
}

int main()
{
    initCurses();

    Window mainW{};
    Editor mainE{};
    
    halfdelay(1);
    while (true)
    {
        ResizeHandle::resize(mainW, mainE);

        mainE.setInput(mainW);
        mainE.updateCursor(mainW);

        if (mainE.getInput() != ERR)
        {
            // newline
            if (mainE.getInput() == 10)
            {
                mainE.print(mainW);
                mainE.addLine();
            }

            // Printable characters
            if (mainE.getInput() >= 32 && mainE.getInput() <= 126)
            {
                mainE.print(mainW);
            }

            // Delete key and backspace
            if (mainE.getInput() == 8 || mainE.getInput() == 127)
            {
                if (mainE.getCursor().x > 0)
                {
                    mainE.popLetter();
                    mvwprintw(mainW.getWin(), mainE.getCursor().y, mainE.getCursor().x - 1, " "); 
                    wmove(mainW.getWin(), mainE.getCursor().y, mainE.getCursor().x - 1);
                }
                else if (mainE.getCursor().y > 0)
                {
                    mainE.popLine();
                    wmove(mainW.getWin(), mainE.getCursor().y - 1, static_cast<int>(std::size(mainE.getData()[static_cast<size_t>(mainE.getCursor().y) - 1]) - 1));
                    mainE.setCursor(Point2D{ mainE.getCursor().y - 1, static_cast<int>(std::size(mainE.getData()[static_cast<size_t>(mainE.getCursor().y) - 1]) - 1)});
                    mainE.popLetter();
                }
            }
        } 

        wrefresh(mainW.getWin());
    }

    getch();
    endwin();
}
