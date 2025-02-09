#ifndef AGGREGATES_H
#define AGGREGATES_H

struct Point2d
{
    int y{};
    int x{};
};

namespace KEY
{
    inline constexpr int NEWLINE{ 10 };
    inline constexpr int BACKSPACE{ 127 };
    inline constexpr int CHARMIN{ 32 };
    inline constexpr int CHARMAX{ 126 };
}

namespace WinType
{
    enum Win : unsigned int
    {
        MAIN = 0,
        SIDE = 1,
        BOTTOM = 2,
        COUNT
    };
}

#endif
