#pragma once

#ifndef RAYCAST_RAY_H
#define RAYCAST_RAY_H

#include "./Shared.h"

struct Ray2D
{
private:
    Vector2D endPos{};
    Vector2D dir{};
    int wallStart3D{};
    int wallEnd3D{};
    int collidedWallType{};
    bool collidedNS{};

public:
    Ray2D() = default;
    Ray2D(const Vector2D& endPos, const Vector2D& dir) : endPos(endPos), dir(dir) {}
    ~Ray2D() = default;

    const Vector2D& GetEndPos() const { return this->endPos; }
    const Vector2D& GetDir() const { return this->dir; }
    const int GetWallStart3D() const { return this->wallStart3D; }
    const int GetWallEnd3D() const { return this->wallEnd3D; }
    const int GetCollidedWallType() const { return this->collidedWallType; }
    const int HasCollidedNS() const { return this->collidedNS; }
    void SetEndPos(const Vector2D& newEndPos) { this->endPos = newEndPos; }
    void SetDir(const Vector2D& newDir) { this->dir = newDir; }
    void SetWallStart3D(int newWallStart3D) { this->wallStart3D = newWallStart3D; }
    void SetWallEnd3D(int newWallEnd3D) { this->wallEnd3D = newWallEnd3D; }
    void SetCollidedWallType(int newCollidedWallType) { this->collidedWallType = newCollidedWallType; }
    void SetCollidedNS(bool newCollidedNS) { this->collidedNS = newCollidedNS; }

};

#endif