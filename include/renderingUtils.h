#include <string>

#include "aggregates.h"
#include "window.h"
#include "resizeHandle.h"
#include "editor.h"

namespace rendering
{
    inline void renderMain(const Editor& editor, const Window& window)
    { 
        window.clearWindow();

        std::size_t offset{ static_cast<std::size_t>(editor.getScrollOffset()) };

        for (std::size_t i{ offset }; i < editor.getData().size() && static_cast<int>(i) - editor.getScrollOffset() < ResizeHandle::getTermSize().y; ++i)
        {
            window.print(editor.getData()[i]);

            if (static_cast<int>(i) - editor.getScrollOffset() != ResizeHandle::getTermSize().y - 1)
                window.print("\n");
        }

        editor.renderCursor(window);
        window.refreshWin();
    }

    inline void renderSide(const Editor& editor, const Window& window)
    {
        window.clearWindow();

        for (int i{ editor.getScrollOffset() }; i - editor.getScrollOffset() < ResizeHandle::getTermSize().y; ++i)
        {
            if (static_cast<int>(editor.getData().size() - 1) < i)
            {
                window.dimOn();
                window.movePrint(i - editor.getScrollOffset(), 0, "~"); 
                window.dimOff();
            }
            else if (editor.getCursor().y == i - editor.getScrollOffset())
            {
                window.boldOn();
                window.movePrint(i - editor.getScrollOffset(), 0, std::to_string(i + 1));
                window.boldOff();
            }
            else
            {
                window.dimOn();
                window.movePrint(i - editor.getScrollOffset(), 0, std::to_string(i + 1)); 
                window.dimOff();
            }
        }

        window.refreshWin();
    }
}
