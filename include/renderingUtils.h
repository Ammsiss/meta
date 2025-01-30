#include <deque>
#include <string>

#include "editor.h"
#include "window.h"
#include "resizeHandle.h"

namespace rendering
{
    // USED HERE
    inline void renderContent(const std::deque<std::string>& data, const Window& window, const int scrollOffset)
    { 
        std::size_t offset{ static_cast<std::size_t>(scrollOffset) };

        for (std::size_t i{ offset }; i < data.size() && static_cast<int>(i) - scrollOffset < ResizeHandle::getTermSize().y; ++i)
        {
            window.print(data[i]);

            if (static_cast<int>(i) - scrollOffset != ResizeHandle::getTermSize().y - 1)
                window.print("\n");
        }
    }

    // USED HERE
    inline void renderCursor(const Cursor& cursor, const Editor& editor, const Window& window)
    {
        window.reverseOn();

        Point2d curP{ cursor.getCursor() };
        int scrollOffset{ cursor.getScrollOffset() };

        if (curP.x == editor.getLineLength(curP.y + scrollOffset))
        {
            window.movePrint(curP.y, curP.x, " ");
        }
        else
        {
            std::size_t logicalY{ static_cast<std::size_t>(cursor.getLogicalY()) };
            std::size_t curX{ static_cast<std::size_t>(curP.x) };
            std::string charToPrint{ editor.getData()[logicalY][curX] };

            window.movePrint(curP.y, curP.x, charToPrint);
        }

        window.reverseOff();
    }
}
