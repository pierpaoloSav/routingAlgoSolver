#include "OutputWindow.h"

OutputWindow::OutputWindow(int width, int height) :
    m_width(width), m_height(height), m_closed(false),
    m_button(width-10-10, 10, 10, 10, "x", 10)
{
    m_text = "";
    m_text1 = "";

    m_scrollOffset = 0.0f;
    m_scrollSpeed = 20.0f;

    setScale((float)GetScreenWidth()/(float)width, (float)GetScreenHeight()/(float)height);
}

void OutputWindow::update()
{
    if (m_button.pressed())
        m_closed = true;

    float wheel = GetMouseWheelMove();
    m_scrollOffset -= wheel * m_scrollSpeed;

    if (m_scrollOffset < 0)
        m_scrollOffset = 0;
    // upper clamp will be handled in render based on content
}

void OutputWindow::setScale(float xScale, float yScale)
{
    m_width = GetScreenWidth();
    m_height = GetScreenHeight();
    
    m_button.setScale(xScale, yScale);
}

void OutputWindow::setText(std::string text)
{
    m_text = text;
}

void OutputWindow::setText1(std::string text)
{
    m_text1 = text;
}

void OutputWindow::setError()
{
    m_err = !m_err;
}

void OutputWindow::render()
{
    // Background
    DrawRectangle(0, 0, m_width, m_height, WHITE);

    int fontSize = 30;
    int lineHeight = fontSize + 5;
    int maxWidth = m_width - 100;

    // Calculate total lines for m_text1 with wrapping
    int totalLines = (!m_text.empty() ? 2 : 0);
    std::string tempLine;
    for (char c : m_text1)
    {
        if (c == '\n')
        {
            totalLines++;
            tempLine.clear();
            continue;
        }
        tempLine += c;
        if (MeasureText(tempLine.c_str(), fontSize) > maxWidth)
        {
            tempLine = std::string(1, c);
            totalLines++;
        }
    }

    float contentHeight = totalLines * lineHeight + 50;
    float maxScroll = std::max(0.0f, contentHeight - m_height);
    if (m_scrollOffset > maxScroll) m_scrollOffset = maxScroll;
    if (m_scrollOffset < 0) m_scrollOffset = 0;

    BeginScissorMode(0, 0, m_width, m_height);

    int x = 50;
    int y = 50 - m_scrollOffset;

    // Render main text
    renderTitle(x, y);

    // Render multiline content
    {
        std::string currentLine;
        for (char c : m_text1)
        {
            if (c == '\n')
            {
                DrawText(currentLine.c_str(), x, y, fontSize, BLACK);
                currentLine.clear();
                y += lineHeight;
                continue;
            }

            currentLine += c;
            if (MeasureText(currentLine.c_str(), fontSize) > maxWidth)
            {
                currentLine.pop_back();
                DrawText(currentLine.c_str(), x, y, fontSize, BLACK);
                currentLine = std::string(1, c);
                y += lineHeight;
            }
        }
        if (!currentLine.empty())
            DrawText(currentLine.c_str(), x, y, fontSize, BLACK);
    }

    EndScissorMode();

    // Scrollbar
    if (contentHeight > m_height)
    {
        float viewHeight = m_height;
        float barHeight = std::max((viewHeight / contentHeight) * viewHeight, 20.0f);
        float scrollRatio = m_scrollOffset / maxScroll;
        float barY = scrollRatio * (viewHeight - barHeight);

        int barWidth = 10;
        int barX = m_width - barWidth - 5;

        DrawRectangle(barX, 0, barWidth, viewHeight, LIGHTGRAY); // track
        DrawRectangle(barX, barY, barWidth, barHeight, DARKGRAY); // thumb
    }

    // Close Button
    m_button.render();
}

// m_text render
void OutputWindow::renderTitle(int& x, int& y)
{
    if (m_text.empty()) return;

    int fontSize = 30;
    int maxWidth = m_width - 100;

    Color textColor = m_err ? RED : BLUE;
    int textFontSize = fontSize;

    // Shrink text if too wide
    while (MeasureText(m_text.c_str(), textFontSize) > maxWidth && textFontSize > 5)
        textFontSize--;

    DrawText(m_text.c_str(), x, y, textFontSize, textColor);
    y += textFontSize + 10;
}

bool OutputWindow::isOpen()
{
    return !m_closed;
}