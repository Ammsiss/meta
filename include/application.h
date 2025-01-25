#include <ncurses.h>

#include <chrono>
#include <thread>

#include "aggregates.h"
#include "window.h"
#include "curses.h"
#include "editor.h"
#include "resizeHandle.h"
#include "input.h"

class Application
{
public:
    Application() = default;

    void initialize()
    {
        m_window.renderCursor(m_cursor.getCursor(), m_editor);
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
        if (m_cursor.getCursor().x != ResizeHandle::getTermSize().x - 1)
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

        m_cursor.setCursorY(true, 1);
        m_cursor.setCursorX(false, 0);
        m_cursor.updateCache();
    }

    void render()
    {
        m_window.clearWindow(); 
        m_window.renderContent(m_editor.getData());
        m_window.renderCursor(m_cursor.getCursor(), m_editor);
    }

    const Window& getWindow() const { return m_window; }

private:
    Window m_window{};
    Editor m_editor{};
    Cursor m_cursor{};
    Input m_input{};
};
