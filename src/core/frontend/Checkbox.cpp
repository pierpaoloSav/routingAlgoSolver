#include "Checkbox.h"

Checkbox::Checkbox(float posX, float posY, int side, const char* title) :
    m_title(title),
    m_fontSizeScaled(m_scaled.height/2),
    m_status(false),
    m_down(false)
{
    //rectangle INIT
    m_case.x = posX;
    m_case.y = posY;
    m_case.width = side;
    m_case.height = side;

    m_scaled = m_case;
}

void Checkbox::event()
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

        m_status = !m_status;
    }
}

bool Checkbox::getStatus()
{
    return m_status;
}

void Checkbox::setScale(float xScale, float yScale)
{
    m_scaled.x = m_case.x*xScale;
    m_scaled.y = m_case.y*yScale;
    m_scaled.width = m_case.width*xScale;
    m_scaled.height = m_case.height*yScale;

    m_fontSizeScaled = m_scaled.height/2*std::min(xScale, yScale);
}

void Checkbox::render()
{
    //rectangle render
    if (m_status)
        DrawRectangleRec(m_scaled, BLUE);
    else
        DrawRectangleLinesEx(m_scaled, 2, BLACK);

    //title render
    int textWidth = MeasureText(m_title, m_fontSizeScaled/2);
    DrawText(m_title, m_scaled.x+(m_scaled.width/2)-(textWidth/2), m_scaled.y+m_scaled.height, m_fontSizeScaled/2, BLACK);
}