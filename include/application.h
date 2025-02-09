#include <chrono>
#include <thread>

#include "aggregates.h"
#include "window.h"
#include "editor.h"
#include "resizeHandle.h"
#include "input.h"
#include "renderingUtils.h"
#include "fileUtils.h"

class Application
{
public:
    Application(const int length, char* clArgs[])
    {
        Point2d term{ ResizeHandle::getTermSize() };

        m_window.emplace_back(Point2d{ term.y, term.x - 4 }, Point2d{ 0, 4 });
        m_window.emplace_back(Point2d{ term.y, 4 }, Point2d{ 0, 0 });

        m_editor.renderCursor(m_window[WinType::MAIN]);
        rendering::renderSide(m_editor, m_window[WinType::SIDE]);

        if (length > 1)
        {
            m_fileName = clArgs[1];
            m_editor.setData(FileUtils::loadFile(m_fileName));
            rendering::renderMain(m_editor, m_window[WinType::MAIN]);
        }
    }

    void run()
    {
        while (true)
        {
            if (ResizeHandle::resize())
            {
                ResizeHandle::resizeMain(m_window[WinType::MAIN]);
                ResizeHandle::resizeSide(m_window[WinType::SIDE]);
            }

            m_input.setInput(m_window[WinType::MAIN]);

            if (m_input.getInput() != ERR)
            {
                m_input.handleInput(m_editor);
                rendering::renderMain(m_editor, m_window[WinType::MAIN]);
                rendering::renderSide(m_editor, m_window[WinType::SIDE]);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }

    const Window& getWindow(std::size_t index) const { return m_window[index]; }

private:
    std::string m_fileName{};

    std::vector<Window> m_window{};
    Editor m_editor{};
    Input m_input{}; 
};
