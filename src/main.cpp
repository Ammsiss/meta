#include <ncurses.h>
#include <signal.h>

#include <vector>
#include <string>
#include <atomic>

#include "resizeHandle.h"

static void initCurses()
{
    initscr();
    cbreak();
    noecho();
    start_color();
    use_default_colors();
    refresh(); 
    signal(SIGWINCH, ResizeHandle::setFlag);
}

int main()
{
    initCurses();

    Window mainW{};

    halfdelay(5);
    while (true)
    {
        ResizeHandle::resize(mainW);


        int input{};
        input = wgetch(mainW.getWin());

        int cy{};
        int cx{};
        getyx(mainW.getWin(), cy, cx);
        if (input != ERR)
        {
            if ((input >= 32 && input <= 126) || input == 10) // all characters
            {
                wprintw(mainW.getWin(), "%c", static_cast<char>(input));
                mainW.appendContent(static_cast<char>(input));
            }
            else if (input == 8 || input == 127) // delete key and backspace
            {
                if (cx > 0)
                {
                    mvwprintw(mainW.getWin(), cy, cx - 1, " "); 
                    wmove(mainW.getWin(), cy, cx - 1);
                    mainW.popContent(); 
                }
                else if (cy > 0)
                {
                    mainW.popContent();
                    wmove(mainW.getWin(), cy - 1, mainW.getPrevLineLength());
                }
            }
        } 

        wrefresh(mainW.getWin());
    }

    getch();
    endwin();
}
