#include <ncurses.h>

#include "resizeHandle.h"
#include "window.h"
#include "application.h"

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

int main(int argc, char* argv[])
{
    initCurses();

    Application app{ argc, argv };
 
    keypad(app.getWindow().getWin(), true);
    nodelay(app.getWindow().getWin(), true);

    app.run();
 
    endwin();
}
