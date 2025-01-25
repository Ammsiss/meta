#ifndef AGGREGATES_H
#define AGGREGATES_H

struct Point2d
{
    int y{};
    int x{};
};

struct CurState
{
    Point2d curP{};
    int cachedX{};
};

namespace KEY
{
    inline constexpr int NEWLINE{ 10 };
    inline constexpr int BACKSPACE{ 127 };
    inline constexpr int CHARMIN{ 32 };
    inline constexpr int CHARMAX{ 126 };
}

#endif
