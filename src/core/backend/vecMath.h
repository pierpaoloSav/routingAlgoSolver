#pragma once

#include <cmath>

struct Vec2 
{
    int x;
    int y;

    bool operator==(const Vec2& other) const 
    {
        return x == other.x && y == other.y;
    }
};

inline int distance(Vec2& A, Vec2& B)
{
    return std::sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}