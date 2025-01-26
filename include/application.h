#include <chrono>
#include <thread>

#include "aggregates.h"
#include "window.h"
#include "curses.h"
#include "editor.h"
#include "resizeHandle.h"
#include "input.h"
#include "renderingUtils.h"

class Application
{
public:
    Application() = default;

    void initialize()
    {
        rendering::renderCursor(m_cursor.getCursor(), m_editor, m_window);
    }

    void run()
    {
        while (true)
        {
            ResizeHandle::resize(m_window);

            m_input.setInput(m_window);

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
            handleCharacter();
        else
        {
            switch (input)
            {
            case KEY::BACKSPACE: handleBackspace(); 
                break;
            case KEY::NEWLINE: handleNewline(); 
                break;
            case KEY_LEFT: m_cursor.moveLeft(); 
                break;
            case KEY_RIGHT: m_cursor.moveRight(m_editor); 
                break;
            case KEY_DOWN: m_cursor.moveDown(m_editor); 
                break;
            case KEY_UP: m_cursor.moveUp(m_editor); 
                break;
            default: 
                break;
            }
        }
    }

    void handleCharacter()
    {
        bool cursorNotAtEnd{ m_cursor.getCursor().x != ResizeHandle::getTermSize().x - 1 };
        bool lineNotFull{ m_editor.getLineLength(m_cursor.getCursor().y) != ResizeHandle::getTermSize().x - 1 };

        if (cursorNotAtEnd && lineNotFull)
        {
            // editor relies on cursor state
            m_editor.addLetter(m_cursor.getCursor(), m_input.getInput());

            m_cursor.setCursorX(true, 1);
            m_cursor.updateCache();
        }
    }

    void handleBackspace()
    {
        if (m_cursor.getCursor().x > 0)
        {
            handleDeleteCharacter();
        }
        else if (m_cursor.getCursor().y > 0)
        {
            handleDeleteLine();
        }
    }

    void handleDeleteCharacter()
    {
        // editor relies on cursor state
        m_editor.popLetter(m_cursor.getCursor());

        m_cursor.setCursorX(true, -1);
        m_cursor.updateCache();
    }

    void handleDeleteLine()
    {
        const int lineLength{ m_editor.getLineLength(m_cursor.getCursor().y - 1) };
        
        // editor relies on cursor state
        m_editor.popLine(m_cursor.getCursor().y);

        m_cursor.setCursorY(true, -1);
        m_cursor.setCursorX(false, lineLength);
        m_cursor.updateCache();
    }

    void handleNewline()
    { 
        // editor relies on cursor state
        m_editor.addLine(m_cursor.getCursor());

        if (!rendering::incrementOffset(m_cursor))
        {
            m_cursor.setCursorY(true, 1);
        }
        m_cursor.setCursorX(false, 0);
        m_cursor.updateCache();
    }

    void render()
    {
        m_window.clearWindow(); 
        rendering::renderContent(m_editor.getData(), m_window);
        rendering::renderCursor(m_cursor.getCursor(), m_editor, m_window);
        mvwprintw(m_window.getWin(), 15, 15, "%d", rendering::incrementOffset(m_cursor));
        m_window.refreshWin();
    }

    const Window& getWindow() const { return m_window; }

private:
    Window m_window{};
    Editor m_editor{};
    Cursor m_cursor{};
    Input m_input{};
};
