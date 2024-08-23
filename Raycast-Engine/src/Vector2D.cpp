#include <cmath>
#include "./headers/Vector2D.h"

Vector2D::Vector2D(float x, float y)
    :
    x(x),
    y(y)
{
}

Vector2D Vector2D::ToNormalized() const
{
    float mag{ sqrt(x * x + y * y) };
    return { x / mag, y / mag };
}

Vector2D Vector2D::ToPerpindicular() const
{
    return{ -y, x };
}

float Vector2D::Magnitude() const
{
    return sqrt(x * x + y * y);
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return { x + other.x, y + other.y };
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return { x - other.x, y - other.y };
}

Vector2D Vector2D::operator*(float scalar) const
{
    return { x * scalar, y * scalar };
}

Vector2D Vector2D::operator/(float scalar) const
{
    return { x / scalar, y / scalar };
}

bool Vector2D::operator==(const Vector2D& other) const
{
    return x == other.x && y == other.y;
}

bool Vector2D::operator!=(const Vector2D& other) const
{
    return x != other.x || y != other.y;
}