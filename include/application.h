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
        m_window.reserve(10);
        m_window.emplace_back();

        m_editor.renderCursor(m_window[WinType::MAIN]);

        if (length > 1)
        {
            m_fileName = clArgs[1];
            m_editor.setData(FileUtils::loadFile(m_fileName));
            render();
        }
    }

    void run()
    {
        while (true)
        {
            ResizeHandle::resize(m_window[WinType::MAIN]);

            m_input.setInput(m_window[WinType::MAIN]);

            if (m_input.getInput() != ERR)
            {
                handleInput();
                render();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }

    void handleInput()
    {
        const int input{ m_input.getInput() };
        const bool isPrintableChar{ input >= KEY::CHARMIN && input <= KEY::CHARMAX };

        if (isPrintableChar)
            m_editor.handleCharacter(m_input);
        else
        {
            switch (input)
            {
            case KEY::BACKSPACE: m_editor.handleBackspace(); 
                break;
            case KEY::NEWLINE: m_editor.handleNewline(); 
                break;
            case KEY_LEFT: m_editor.moveLeft(); 
                break;
            case KEY_RIGHT: m_editor.moveRight(); 
                break;
            case KEY_DOWN: m_editor.moveDown(); 
                break;
            case KEY_UP: m_editor.moveUp(); 
                break;
            default: 
                break;
            }
        }
    }

    void render()
    {
        m_window[WinType::MAIN].clearWindow(); 
        rendering::renderContent(m_editor.getData(), m_window[WinType::MAIN], m_editor.getScrollOffset());
        m_editor.renderCursor(m_window[WinType::MAIN]);

        m_window[WinType::MAIN].refreshWin();
    }

    const Window& getWindow(std::size_t index) const { return m_window[index]; }

private:
    std::string m_fileName{};

    std::vector<Window> m_window{};
    Editor m_editor{};
    Input m_input{}; 
};
