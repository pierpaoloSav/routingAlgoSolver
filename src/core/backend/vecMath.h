#pragma once

#include <cmath>

template <typename T>
struct Vec2T
{
    T x;
    T y;

    Vec2T() = default;

    Vec2T(T xVal, T yVal) : x(xVal), y(yVal) {}

    bool operator==(const Vec2T<T>& other) const
    {
        return x == other.x && y == other.y;
    }

    // Conversion constructor (allows Vec2<int> -> Vec2<float> and vice versa)
    template <typename U>
    Vec2T(const Vec2T<U>& other)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
};
// Alias
using Vec2 = Vec2T<int>;
using Vec2f = Vec2T<float>;

template <typename T>
inline float distance(const Vec2T<T>& A, const Vec2T<T>& B)
{
    return std::sqrt(
        (A.x - B.x)*(A.x - B.x) +
        (A.y - B.y)*(A.y - B.y)
    );
}