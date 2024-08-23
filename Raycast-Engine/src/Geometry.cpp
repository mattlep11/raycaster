#include "./headers/Geometry.h"

Vector2D ApplyRotationMatrix(const Vector2D& vec, float alpha)
{
    return { vec.GetX() * cos(alpha) - vec.GetY() * sin(alpha), vec.GetX() * sin(alpha) + vec.GetY() * cos(alpha) };
}