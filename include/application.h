#include <chrono>
#include <thread>

#include "aggregates.h"
#include "window.h"
#include "curses.h"
#include "editor.h"
#include "resizeHandle.h"
#include "input.h"
#include "renderingUtils.h"
#include "fileUtils.h"
#include "cursor.h"

class Application
{
public:
    Application(const int length, char* clArgs[])
    {
        m_window.reserve(10);
        m_window.emplace_back();

        rendering::renderCursor(m_cursor, m_editor, m_window[WinType::MAIN]);

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
        // POTENTIALLY CAN CHANGE
        bool lineNotFull{ m_editor.getLineLength(m_cursor.getLogicalY()) != ResizeHandle::getTermSize().x - 1 };

        if (cursorNotAtEnd && lineNotFull)
        {
            // editor relies on cursor state
            m_editor.addLetter(Point2d{ m_cursor.getLogicalY(), m_cursor.getCursor().x }, m_input.getInput());

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
        else if (m_cursor.getScrollOffset() != 0 || m_cursor.getCursor().y != 0)
        {
            handleDeleteLine();
        }
    }

    void handleDeleteCharacter()
    {
        // editor relies on cursor state
        m_editor.popLetter(Point2d{ m_cursor.getLogicalY(), m_cursor.getCursor().x });

        m_cursor.setCursorX(true, -1);
        m_cursor.updateCache();
    }

    void handleDeleteLine()
    {
        const int lineLength{ m_editor.getLineLength(m_cursor.getLogicalY() - 1) };
        
        if (m_cursor.getCursor().y != 0)
        {
            // editor relies on cursor state
            m_editor.popLine(m_cursor.getLogicalY()); 

            m_cursor.setCursorY(true, -1);
            m_cursor.setCursorX(false, lineLength);
            m_cursor.updateCache();
        }
        else
        {
            m_editor.popLine(m_cursor.getLogicalY());

            m_cursor.decrementOffset();
            m_cursor.setCursorX(false, lineLength);
            m_cursor.updateCache();
        }
    }

    void handleNewline()
    { 
        // editor relies on cursor state
        m_editor.addLine(Point2d{ m_cursor.getLogicalY(), m_cursor.getCursor().x });

        if (m_cursor.getCursor().y == ResizeHandle::getTermSize().y - 1)
            m_cursor.incrementOffset();
        else
            m_cursor.setCursorY(true, 1);

        m_cursor.setCursorX(false, 0);
        m_cursor.updateCache();
    }

    void render()
    {
        m_window[WinType::MAIN].clearWindow(); 
        rendering::renderContent(m_editor.getData(), m_window[WinType::MAIN], m_cursor.getScrollOffset());
        rendering::renderCursor(m_cursor, m_editor, m_window[WinType::MAIN]);

        m_window[WinType::MAIN].refreshWin();
    }

    const Window& getWindow(std::size_t index) const { return m_window[index]; }

private:
    std::string m_fileName{};

    std::vector<Window> m_window{};
    Editor m_editor{};
    Cursor m_cursor{};
    Input m_input{}; 
};
