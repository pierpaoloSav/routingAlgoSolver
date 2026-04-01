#include "TextCase.h"

TextCase::TextCase(float posX, float posY, int width, int height, int max) :
    m_title(nullptr),
    m_fontSize(height),
    m_fontSizeScaled(height),
    m_max(max),
    m_valid(nullptr),

    m_isUsing(false),
    m_down(false)
{
    // Rectangle INIT
    m_case.x = posX;
    m_case.y = posY;
    m_case.width = width;
    m_case.height = height;

    m_scaled = m_case;
}

TextCase::~TextCase()
{
    delete m_valid;
    m_valid = nullptr;
}

void TextCase::event()
{
    // Check if selected
        // Get values
        int x = GetMouseX();
        int y = GetMouseY();
        static bool inside = false;
        inside = (x > m_scaled.x && x < m_scaled.x + m_scaled.width 
                && y > m_scaled.y && y < m_scaled.y + m_scaled.height);

        // Mouse pressed
        if (IsMouseButtonPressed(0))
        {
            m_down = inside;
        }

        // If mouse has been pressed but is no longer inside the button
        if (!inside)
            m_down = false;

        // Mouse released
        if (IsMouseButtonReleased(0))
        {
            m_isUsing = inside*m_down;
            m_down = false;
        }

    // Check writing
    if (m_isUsing)
    {
        char keyC = GetCharPressed();
        int key = GetKeyPressed();
        
        // Delete with backspace
        if (IsKeyPressed(KEY_BACKSPACE) && !m_text.empty())
            m_text.pop_back(); 

        // Check if the char is valid (if there are restrictions)
        if (m_valid)
        {
            if (keyC && m_valid && !m_valid->count(keyC))
                return;
        }
        // Write char
        if (keyC && m_text.size() < m_max)
            m_text += keyC;
    }    
}

void TextCase::render()
{
    // Rectangle render
    if (m_isUsing || m_down)
        DrawRectangleLinesEx(m_scaled, 2, BLUE);
    else
        DrawRectangleLinesEx(m_scaled, 2, BLACK);

    float xMargin = m_scaled.width * 0.05f;   
    float yMargin = m_scaled.height * 0.1f;  

    // Text render (scrolling if too wide)
    const char* sText = m_text.c_str();
    float availableWidth = m_scaled.width - 2 * xMargin;
    int textLen = m_text.length();
    int startIdx = 0;
    // Find substring to fit if too wide
    if (MeasureText(sText, m_fontSizeScaled) > availableWidth) {
        // Try to find the minimal substring from the end that fits
        for (int i = 0; i < textLen; ++i) {
            const char* sub = sText + i;
            if (MeasureText(sub, m_fontSizeScaled) <= availableWidth) {
                startIdx = i;
                break;
            }
        }
    }
    const char* drawText = sText + startIdx;
    DrawText(drawText, m_scaled.x + xMargin, m_scaled.y + yMargin, m_fontSizeScaled, BLACK);

    // Title render
    if (m_title)
    {
        int titleSize = m_fontSizeScaled * 0.7f; // titolo leggermente più piccolo
        DrawText(m_title, m_scaled.x + xMargin, m_scaled.y - titleSize - yMargin, titleSize, BLACK);
    }
}

std::string TextCase::getText()
{
    return m_text;
}

void TextCase::clearText()
{
    m_text = "";
}

void TextCase::setScale(float xScale, float yScale)
{
    m_scaled.x = m_case.x*xScale;
    m_scaled.y = m_case.y*yScale;
    m_scaled.width = m_case.width*xScale;
    m_scaled.height = m_case.height*yScale;

    m_fontSizeScaled = m_fontSize*std::min(xScale, yScale);
}

void TextCase::setTitle(const char *title)
{
    m_title = title;
}

void TextCase::setValid(std::unordered_set<char> &valid)
{
    m_valid = new std::unordered_set<char>(valid);
}

void TextCase::unSelect()
{
    m_isUsing = false;
}