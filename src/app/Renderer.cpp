#include "Renderer.h"

void Renderer::drawNode(Node &n)
{
    DrawCircleLines(n.getX(), n.getY(), n.getRadius(), BLACK);

    std::string t = "";
    t+=n.getTitle();
    Vector2 tPos = { n.getX() - (float)(MeasureText(t.c_str(), n.getRadius()) /2), 
                     n.getY() - (float)(n.getRadius() /2)};
    DrawText(t.c_str(), tPos.x, tPos.y, n.getRadius(), BLACK);                    
}

void Renderer::drawEdge(Edge &e)
{
    Vector2 p0 = {(float)e.getP().x, (float)e.getP().y};
    Vector2 p1 = {(float)e.getP1().x, (float)e.getP1().y};

    //Draw Line
        // Direction vector from p0 to p1
        Vector2 dir = {p1.x - p0.x, p1.y - p0.y};

        // Length of the segment
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);

        // Normalize direction (length = 1)
        dir.x /= len;
        dir.y /= len;

        // Move points
        p0.x += dir.x * NODE_RADIUS;
        p0.y += dir.y * NODE_RADIUS;

        p1.x -= dir.x * NODE_RADIUS;
        p1.y -= dir.y * NODE_RADIUS;

        DrawLineEx(p0, p1, 2.0f, BLACK);
    
    // Arrowhead
        float arrowScale = 0.7f;
        float arrowSize = NODE_RADIUS * arrowScale;

        // Perpendicular vector (normalized)
        Vector2 perp = { -dir.y, dir.x };
        float perpLen = sqrt(perp.x * perp.x + perp.y * perp.y);
        if (perpLen != 0)
        {
            perp.x /= perpLen;
            perp.y /= perpLen;
        }

        // Place tip exactly at the node edge
        Vector2 tip = p1;

        Vector2 base = {
            tip.x - dir.x * arrowSize,
            tip.y - dir.y * arrowSize
        };

        Vector2 left = {
            base.x + perp.x * (arrowSize * 0.6f),
            base.y + perp.y * (arrowSize * 0.6f)
        };

        Vector2 right = {
            base.x - perp.x * (arrowSize * 0.6f),
            base.y - perp.y * (arrowSize * 0.6f)
        };

        DrawTriangle(tip, right, left, BLACK);

    // Weight Text rotated
        std::string weightStr = std::to_string(e.getWeight());
        std::string text;
        Font font = GetFontDefault();

        // Position (edge center)
        Vector2 pos = {(float)e.getMidP().x, (float)e.getMidP().y};

        // Edge angle
        float angle = atan2(dir.y, dir.x) * RAD2DEG;

        
        // Adding direction to the text
        bool flipped = false;
        if (angle > 90 || angle < -90)
        {
            angle += 180;
            flipped = true;
        }
        if (flipped)
            text = "< " + weightStr;
        else
            text = weightStr + " >";

        // Text size to center it
        Vector2 textSize = MeasureTextEx(font, text.c_str(), NODE_RADIUS, 1);
        Vector2 origin = { textSize.x / 2.0f, textSize.y / 2.0f };

        // Offset
        pos.x += perp.x * 10;
        pos.y += perp.y * 10;

        DrawTextPro(
            font,
            text.c_str(),
            pos,
            origin,
            angle,
            NODE_RADIUS,
            1,
            BLACK
        );
}

void Renderer::drawXMargin(int y, int lenght)
{
    DrawLine(0, y, lenght, y, BLACK);
    DrawRectangle(0, y, lenght, y, WHITE);
}

void Renderer::drawYMargin(int x, int lenght)
{
    DrawLine(x, 0, x, lenght, BLACK);
    DrawRectangle(x, 0, x, lenght, WHITE);
}