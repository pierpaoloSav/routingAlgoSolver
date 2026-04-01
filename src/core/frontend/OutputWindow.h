#pragma once

#include <raylib.h>
#include <string>

#include "Button.h"

class OutputWindow
{
public:
    OutputWindow(int width, int height);

    void update();
    void render();

    void setScale(float xScale, float yScale);
    void setText(std::string text);
    void setText1(std::string text);
    void setError();

    bool isOpen();

private:
    void renderTitle(int& x, int& y);

private:
    Button m_button;
    int m_width;
    int m_height;

    float m_scrollOffset;
    float m_scrollSpeed;

    std::string m_text;
    std::string m_text1;
    bool m_err;

    bool m_closed;
};