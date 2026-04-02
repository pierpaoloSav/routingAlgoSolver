#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "vecMath.h"

class Node
{
public:
    Node(Vec2 c, int radius, std::string title);
    
    float disCenter(Vec2 p);

    int getRadius();
    Vec2 getCenter();
    int getX();
    int getY();
    std::string getTitle();

private:
    int m_radius;
    Vec2 m_c;
    std::string m_title;
};