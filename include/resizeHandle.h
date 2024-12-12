#ifndef RESIZE_HANDLE
#define RESIZE_HANDLE

#include <atomic>

#include "window.h"

class ResizeHandle
{
public:
    static void setFlag(int sig);
    static void getSize(int& rows, int& cols);
    static void resize(Window& mainW);

private:
    static inline std::atomic<bool> s_resizeFlag{ false };
 
    static void resizeStdscr();
};

#endif
