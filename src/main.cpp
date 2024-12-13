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
            // newline
            if(input == 10)
            {
                mainW.appendData(cy, '\n');
                mainW.newLine();
                wprintw(mainW.getWin(), "%c", '\n');
            }

            // Printable characters
            if (input >= 32 && input <= 126)
            {
                mainW.appendData(cy, static_cast<char>(input));
                wprintw(mainW.getWin(), "%c", static_cast<char>(input));
            }
            
            // Delete key and backspace
            if (input == 8 || input == 127)
            {
                if (cx > 0)
                {
                    mainW.popData(cy); 
                    mvwprintw(mainW.getWin(), cy, cx - 1, " "); 
                    wmove(mainW.getWin(), cy, cx - 1);
                }
                else if (cy > 0)
                {
                    mainW.delLine();
                    mainW.popData(cy - 1);
                    wmove(mainW.getWin(), cy - 1, mainW.getLineLength(cy - 1));
                }
            }
        } 

        wrefresh(mainW.getWin());
    }

    getch();
    endwin();
}
