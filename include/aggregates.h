#ifndef AGGREGATES_H
#define AGGREGATES_H

#include <optional>

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

#endif
