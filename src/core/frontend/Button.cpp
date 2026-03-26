#include "Button.h"

Button::Button(float posX, float posY, int width, int height, const char* title, int fontSize) :
    m_title(title),
    m_fontSize(fontSize),
    m_fontSizeScaled(fontSize),
    m_down(false)
{
    //rectangle INIT
    m_case.x = posX;
    m_case.y = posY;
    m_case.width = width;
    m_case.height = height;
    m_scaled = m_case;
}

bool Button::pressed()
{
    //get values
    int x = GetMouseX();
    int y = GetMouseY();
    static bool inside = false;
    inside = (x > m_scaled.x && x < m_scaled.x + m_scaled.width 
                && y > m_scaled.y && y < m_scaled.y + m_scaled.height);

    //mouse pressed
    if (IsMouseButtonPressed(0))
        m_down = inside;

    //if mouse has been pressed but is no longer inside the button
    if (!inside)
        m_down = false;

    //mouse released
    if (IsMouseButtonReleased(0) && m_down)
    {
        m_down = false;

        return inside;
    }

    return false;
}

void Button::setScale(float xScale, float yScale)
{
    m_scaled.x = m_case.x*xScale;
    m_scaled.y = m_case.y*yScale;
    m_scaled.width = m_case.width*xScale;
    m_scaled.height = m_case.height*yScale;

    m_fontSizeScaled = m_fontSize*std::min(xScale, yScale);
}

void Button::render()
{
    //rectangle render
    if (m_down)
        DrawRectangleLinesEx(m_scaled, 2, BLUE);
    else
        DrawRectangleLinesEx(m_scaled, 2, BLACK);

    //title render
    int textWidth = MeasureText(m_title, m_fontSizeScaled);
    DrawText(m_title, m_scaled.x+(m_scaled.width/2)-(textWidth/2), 
             m_scaled.y+(m_scaled.height/2)-(m_fontSizeScaled/2), 
             m_fontSizeScaled, BLACK);
}