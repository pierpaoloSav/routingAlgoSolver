#include "Window.h"

Window::Window(int width, int height, const char* title)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, title);
}

Window::~Window()
{
    CloseWindow();
}

void Window::setMinSize(int width, int height)
{
    SetWindowMinSize(width, height);
}

bool Window::isOpen()
{
    return !WindowShouldClose();
}