#ifndef AGGREGATES_H
#define AGGREGATES_H

struct Point2d
{
    int y{};
    int x{};
};

namespace Constants
{
    inline constexpr int newline{ 10 };
    inline constexpr int backspace{ 127 };
    inline constexpr int printableCharMin{ 32 };
    inline constexpr int printableCharMax{ 126 };
}

#endif
