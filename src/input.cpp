#include "input.h"
#include "editor.h"

void Input::handleInput(Editor& editor)
{
    const int input{ getInput() };
    const bool isPrintableChar{ input >= KEY::CHARMIN && input <= KEY::CHARMAX };

    if (isPrintableChar)
        editor.handleCharacter(*this);
    else
    {
        switch (input)
        {
        case KEY::BACKSPACE: editor.handleBackspace(); 
            break;
        case KEY::NEWLINE: editor.handleNewline(); 
            break;
        case KEY_LEFT: editor.moveLeft(); 
            break;
        case KEY_RIGHT: editor.moveRight(); 
            break;
        case KEY_DOWN: editor.moveDown(); 
            break;
        case KEY_UP: editor.moveUp(); 
            break;
        default: 
            break;
        }
    }
}

