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
                handleInput();
                render();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }

    void handleInput()
    {
        if (m_editor.getInput() == Constants::newline)
        {
            handleNewline();
        }
        else if (m_editor.getInput() >= Constants::printableCharMin && m_editor.getInput() <= Constants::printableCharMax)
        {
            handleCharacter();
        }
        else if (m_editor.getInput() == Constants::backspace)
        {
            if (m_cursor.getCursor().x > 0)
                handleDeleteCharacter();
            else if (m_cursor.getCursor().y > 0)
                handleDeleteLine();
        }
        else if (m_editor.getInput() == KEY_LEFT)
        {
            if (m_cursor.getCursor().x != 0)
            {
                m_cursor.setCursor(Point2d{ 0, -1 });
                m_cursor.setCachedX(m_cursor.getCursor().x);
            }
        }
        else if (m_editor.getInput() == KEY_RIGHT)
        {
            if (m_cursor.getCursor().x != m_editor.getLineLength(m_cursor.getCursor().y))
            {
                m_cursor.setCursor(Point2d{ 0, 1 });
                m_cursor.setCachedX(m_cursor.getCursor().x);
            }
        }
        else if (m_editor.getInput() == KEY_UP)
        {
            Point2d curP{ m_cursor.getCursor() };
            int cachedX{ m_cursor.getCahcedX() };

            if (curP.y != 0)
            {
                if (cachedX <= m_editor.getLineLength(curP.y - 1))
                    m_cursor.setCursor(Point2d{ -1, 0 }, cachedX);
                else
                    m_cursor.setCursor(Point2d{ -1, 0 }, m_editor.getLineLength(curP.y - 1));
            }
        }
        else if (m_editor.getInput() == KEY_DOWN)
        {
            Point2d curP{ m_cursor.getCursor() };
            int cachedX{ m_cursor.getCahcedX() };

            if (curP.y != static_cast<int>(m_editor.getData().size()) - 1)
            {
                if (cachedX <= m_editor.getLineLength(curP.y + 1))
                    m_cursor.setCursor(Point2d{ 1, 0 }, cachedX);
                else
                    m_cursor.setCursor(Point2d{ 1, 0 }, m_editor.getLineLength(curP.y + 1));
            }
        }
    }

    void handleCharacter()
    {
        m_editor.addLetter(m_cursor);

        m_cursor.setCursor(Point2d{ 0, 1 });
        m_cursor.setCachedX(m_cursor.getCursor().x); 
    }

    void handleDeleteCharacter()
    {
        m_editor.popLetter(m_cursor);

        m_cursor.setCursor(Point2d{ 0, -1 });
        m_cursor.setCachedX(m_cursor.getCursor().x);  
    }

    void handleNewline()
    {
        m_editor.addLine(m_cursor);

        m_cursor.setCursor(Point2d{ 1, 0 }, 0);
        m_cursor.setCachedX(0);
    }

    void handleDeleteLine()
    {
        int curY{ m_cursor.getCursor().y };

        int previousLineLength{ m_editor.getLineLength(m_cursor.getCursor().y - 1) };

        m_cursor.setCursor(Point2d{ -1, 0 }, previousLineLength);
        m_cursor.setCachedX(m_cursor.getCursor().x); 

        m_editor.popLine(curY);    
    }

    void render()
    {
        m_window.clearWindow(); 
        m_window.renderContent(m_editor.getData());
        m_window.renderCursor(m_cursor, m_editor);

        mvwprintw(m_window.getWin(), 15, 15, "%d", m_cursor.getCahcedX());
        wrefresh(m_window.getWin()); 
    }

    const Window& getWindow() const { return m_window; }

private:
    Window m_window{};
    Editor m_editor{};
    Cursor m_cursor{};
};
