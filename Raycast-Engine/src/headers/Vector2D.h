#pragma once

#ifndef RAYCAST_2D_VECTOR_H
#define RAYCAST_2D_VECTOR_H

struct Vector2D
{
private:
    float x{};
    float y{};

public:
    Vector2D() = default;
    ~Vector2D() = default;
    Vector2D(float x, float y);
    Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;
    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;

    // normalizes the vector and returns a copy
    Vector2D ToNormalized() const;
    // returns a perpindicular vector
    Vector2D ToPerpindicular() const;
    // returns the magnitude of this vector
    float Magnitude() const;

    float GetX() const { return this->x; }
    float GetY() const { return this->y; }
    void SetX(float newX) { this->x = newX; }
    void SetY(float newY) { this->y = newY; }
};

#endif