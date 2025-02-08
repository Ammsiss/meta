#include <string>

#include "window.h"
#include "resizeHandle.h"
#include "editor.h"

namespace rendering
{
    inline void render(const Editor& editor, const Window& window)
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

}
