#include "./headers/Geometry.h"

Vector2D ApplyRotationMatrix(const Vector2D& vec, float alpha)
{
    return { vec.GetX() * cos(alpha) - vec.GetY() * sin(alpha), vec.GetX() * sin(alpha) + vec.GetY() * cos(alpha) };
}

float CircToSquareDist(const Vector2D& circ, const Vector2D& sq, int width)
{
    Vector2D closest{ CircToSquareClosestPoint(circ, sq, width) };
    float px{ closest.GetX() };
    float py{ closest.GetY() };
    float cx{ circ.GetX() };
    float cy{ circ.GetY() };

    return sqrt((px - cx) * (px - cx) + (py - cy) * (py - cy));
}

Vector2D CircToSquareClosestPoint(const Vector2D& circ, const Vector2D& sq, int width)
{
    float sx{ sq.GetX() };
    float sy{ sq.GetY() };

    return{ clamp(circ.GetX(), sx, sx + width), clamp(circ.GetY(), sy, sy + width) };
}

bool CircToSquareIsColliding(const Vector2D& circ, float radius, const Vector2D& sq, int width)
{
    return CircToSquareDist(circ, sq, width) < radius;
}
