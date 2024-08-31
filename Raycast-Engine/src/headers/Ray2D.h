#pragma once

#ifndef RAYCAST_RAY_H
#define RAYCAST_RAY_H

#include "./Shared.h"

struct Ray2D
{
private:
    Vector2D endPos{};
    Vector2D dir{};

public:
    Ray2D() = default;
    Ray2D(const Vector2D& endPos, const Vector2D& dir) : endPos(endPos), dir(dir) {}
    ~Ray2D() = default;

    const Vector2D& GetEndPos() const { return this->endPos; }
    const Vector2D& GetDir() const { return this->dir; }
    void SetEndPos(const Vector2D& newEndPos) { this->endPos = newEndPos; }
    void SetDir(const Vector2D& newDir) { this->dir = newDir; }
};

#endif