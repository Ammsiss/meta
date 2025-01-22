#include <ncurses.h>

#include "resizeHandle.h"
#include "window.h"
#include "cursor.h"
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

int main()
{
    initCurses();

    Application app{};
    app.initialize();
 
    keypad(app.getWindow().getWin(), true);
    nodelay(app.getWindow().getWin(), true);

    app.run();
 
    endwin();
}
