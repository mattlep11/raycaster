#pragma once

#ifndef RAYCAST_GEOMETRY_HELPERS_H
#define RAYCAST_GEOMETRY_HELPERS_H

#include <cmath>
#include "./Shared.h"
#include "./Vector2D.h"

// applies the rotation matrix to rotate a vector a certain alpha degrees
Vector2D ApplyRotationMatrix(const Vector2D& vec, float alpha);

// returns the distance between a circle and a square
float CircToSquareDist(const Vector2D& circ, const Vector2D& sq, int width);

// returns a vector of the closest point to the circle on a square
Vector2D CircToSquareClosestPoint(const Vector2D& circ, const Vector2D& sq, int width);

// returns true if a circle is colliding with a square
bool CircToSquareIsColliding(const Vector2D& circ, float radius, const Vector2D& sq, int width);

#endif