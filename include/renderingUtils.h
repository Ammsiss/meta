#include <deque>
#include <string>

#include "window.h"
#include "resizeHandle.h"

namespace rendering
{
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
}
