#ifndef EDITOR_H
#define EDITOR_H

#include "aggregates.h"

class Editor
{
public:
    Editor(const Point2D cursorPosition);

private:
    Point2D m_cursorPosition{};
};

#endif
