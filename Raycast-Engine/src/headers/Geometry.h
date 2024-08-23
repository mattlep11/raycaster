#pragma once

#ifndef RAYCAST_GEOMETRY_HELPERS_H
#define RAYCAST_GEOMETRY_HELPERS_H

#include <cmath>
#include "./Vector2D.h"

// applies the rotation matrix to rotate a vector a certain alpha degrees
Vector2D ApplyRotationMatrix(const Vector2D& vec, float alpha);

#endif