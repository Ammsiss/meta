#ifndef RESIZE_HANDLE
#define RESIZE_HANDLE

#include <sys/ioctl.h>
#include <unistd.h>

#include "aggregates.h"

class Window;

class ResizeHandle
{
public:
    static void resize(Window& win);
    static Point2d getTermSize();
    static void initialize(); 

private: 
    static void setTermSize(int& rows, int& cols);

    static inline Point2d termSize{};
};

#endif
