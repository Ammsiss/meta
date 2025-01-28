#include <deque>
#include <string>

#include "editor.h"
#include "window.h"
#include "resizeHandle.h"

namespace rendering
{
    inline int scrollOffset{ 0 };

    // returns true if incremented scroll offset
    inline bool incrementOffset(const Cursor& cursor)
    {
        if (cursor.getCursor().y == ResizeHandle::getTermSize().y - 1)
        {
            ++scrollOffset;
            return true;
        }

        return false;
    }

    inline void decrementOffset()
    {
        --scrollOffset;
    }

    inline void renderContent(const std::deque<std::string>& data, const Window& window)
    { 
        /*
        window.moveCursor(0, 0);

        for (const auto& line : data)
        {            
            window.print(line);
            window.print("\n");
        }
        */

        std::size_t offset{ static_cast<std::size_t>(rendering::scrollOffset) };

        for (std::size_t i{ offset }; i < data.size() && static_cast<int>(i) - scrollOffset < ResizeHandle::getTermSize().y; ++i)
        {
            window.print(data[i]);

            if (static_cast<int>(i) - scrollOffset != ResizeHandle::getTermSize().y - 1)
                window.print("\n");
        }
    }

    inline void renderCursor(const Point2d curP, const Editor& editor, const Window& window)
    {
        window.reverseOn();

        if (curP.x == editor.getLineLength(curP.y + scrollOffset))
        {
            window.movePrint(curP.y, curP.x, " ");
        }
        else
        {
            std::size_t curY{ static_cast<std::size_t>(curP.y + scrollOffset) };
            std::size_t curX{ static_cast<std::size_t>(curP.x) };
            std::string charToPrint{ editor.getData()[curY][curX] };

            window.movePrint(curP.y, curP.x, charToPrint);
        }

        window.reverseOff();
    }
}
