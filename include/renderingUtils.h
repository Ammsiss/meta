#include <deque>
#include <string>

#include "editor.h"
#include "window.h"

namespace rendering
{
    inline void renderContent(const std::deque<std::string>& data, const Window& window)
    { 
        window.moveCursor(0, 0);

        for (const auto& line : data)
        {            
            window.print(line);
            window.print("\n");
        }
    }

    inline void renderCursor(const Point2d curP, const Editor& editor, const Window& window)
    {
        window.reverseOn();

        if (curP.x == editor.getLineLength(curP.y))
        {
            window.movePrint(curP.y, curP.x, " ");
        }
        else
        {
            std::size_t curY{ static_cast<std::size_t>(curP.y) };
            std::size_t curX{ static_cast<std::size_t>(curP.x) };
            std::string charToPrint{ editor.getData()[curY][curX] };

            window.movePrint(curP.y, curP.x, charToPrint);
        }

        window.reverseOff();
    }
}
