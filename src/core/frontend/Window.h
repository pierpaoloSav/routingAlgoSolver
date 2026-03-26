#pragma once

#include <raylib.h>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    void setMinSize(int width, int height);

    bool isOpen();

private:
    int m_minWidth;
    int m_minHeight;
};