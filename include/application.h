#include <ncurses.h>

#include <chrono>
#include <thread>

#include "aggregates.h"
#include "window.h"
#include "curses.h"
#include "editor.h"
#include "resizeHandle.h"

class Application
{
public:
    Application() = default;

    void initialize()
    {
        m_window.renderCursor(m_cursor, m_editor);
    }

    void run()
    {
        while (true)
        {
            ResizeHandle::resize(m_window);

            m_editor.setInput(wgetch(m_window.getWin()));

            if (m_editor.getInput() != ERR)
            {
                m_cursor.updateCursorState();
                handleInput();
                render();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }

    void handleInput()
    {
        const int input{ m_editor.getInput() };
        const bool isPrintableChar{ input >= KEY::CHARMIN && input <= KEY::CHARMAX };

        if (isPrintableChar)
            handleCharacter();
        else
        {
            switch (input)
            {
            case KEY::NEWLINE: handleNewline(); 
                break; 
            case KEY::BACKSPACE: handleBackspace(); 
                break;
            case KEY_LEFT: m_cursor.handleLeft(); 
                break;
            case KEY_RIGHT: m_cursor.handleRight(m_editor.getLineLength(m_cursor.getCursor().y)); 
                break;
            case KEY_DOWN: m_cursor.handleDown(m_editor); 
                break;
            case KEY_UP: m_cursor.handleUp(m_editor); 
                break;
            default: 
                break;
            }
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

    void handleCharacter()
    {
        m_editor.addLetter(m_cursor.getCursorState().curP);
        m_cursor.handleRight(m_editor.getLineLength(m_cursor.getCursor().y));
    }

    void handleDeleteCharacter()
    {
        m_editor.popLetter(m_cursor.getCursorState().curP);
        m_cursor.handleLeft(); 
    }

    void handleNewline()
    {
        m_editor.addLine(m_cursor.getCursorState().curP);

        // m_window.incrementOffset(m_cursor.getCursorState().curP.y);
        
        m_cursor.handleDown(m_editor);
        m_cursor.setX(0);
        m_cursor.setCachedX(0);
    }

    void handleDeleteLine()
    {
        m_cursor.handleUp(m_editor, m_editor.getLineLength(m_cursor.getCursor().y - 1));

        m_editor.popLine(m_cursor.getCursorState().curP.y);
    }

    void render()
    {
        m_window.clearWindow(); 
        m_window.renderContent(m_editor.getData());
        m_window.renderCursor(m_cursor, m_editor);
        
        mvwprintw(m_window.getWin(), 15, 15, "cx: %d", m_cursor.getCahcedX());
        mvwprintw(m_window.getWin(), 16, 15, "y:  %d", m_cursor.getCursor().y);
        mvwprintw(m_window.getWin(), 17, 15, "x:  %d", m_cursor.getCursor().x);
        mvwprintw(m_window.getWin(), 18, 15, "l1: %d", m_editor.getLineLength(0));
        mvwprintw(m_window.getWin(), 19, 15, "IO: %d", m_window.getOffset()); 
        wrefresh(m_window.getWin());
    }

    const Window& getWindow() const { return m_window; }

private:
    Window m_window{};
    Editor m_editor{};
    Cursor m_cursor{};
};
