#pragma once

#ifndef RAYCAST_PLAYER_H
#define RAYCAST_PLAYER_H

#include "./Shared.h"
#include "./Grid.h"
#include "./Ray2D.h"

class Grid; // forward declaration to avoid circular dependency errrors
class Player
{
    Ray2D rays[NB_RAYS]{};

    Vector2D pos{ VIEW_START_X + VIEW_WIDTH * 0.5f, VIEW_START_Y + VIEW_HEIGHT * 0.5f };
    Vector2D dir{ 0.0f, -1.0f };
    static constexpr float radius{ CELL_WIDTH / 2.0f };

    static constexpr float dirLength{ DIR_VEC_LENGTH };
    static constexpr float viewLength{ VIEW_VEC_LENGTH };
    float fov{ atanf(dirLength / viewLength) * 2.0f };

    Vector2D viewPointL{ pos - Vector2D(viewLength * 0.5f, 0.0f) }; // the left-most point of the view plane
    Vector2D viewPointR{ pos + Vector2D(viewLength * 0.5f, 0.0f) }; // the right-most point of the view plane
    Vector2D dirPoint{ pos - Vector2D(0.0f, dirLength) }; // middle-most point of the view plane, end of direction vec.

    // updates the position of the player based on current user inputs
    void UpdatePosition(float v, float strafe, float av);
    // updates the rotation of the player based on current user inputs
    void UpdateRotation(float av);
    // checks to see if the player is currently overlapping any grid tiles
    void CheckCollisionStatus(const Grid& grid);
    // resolves any found collision with grid tiles
    void ResolveCollision(const Vector2D& wall);
    // updates the angles of all rays in the ray array
    void UpdateRayOrientations();
    // performs the digital differential analyzer algorithm to extend the rays until a collision point
    void Raycast(const Grid& grid, Ray2D& ray);

public:
    Player();
    ~Player() = default;
    // updates the player with new user input
    void Update(const Grid& grid, float v, float strafe, float av);

    const Vector2D GetPos() const { return this->pos; }
    const Vector2D GetDir() const { return this->dir; }
    const float GetDirLength() const { return this->dirLength; }
    const Vector2D GetViewPointL() const { return this->viewPointL; }
    const Vector2D GetViewPointR() const { return this->viewPointR; }
    const Vector2D GetDirPoint() const { return this->dirPoint; }
    const Ray2D* GetRays() const { return this->rays; }
    float GetRadius() const { return this->radius; }
};

#endif