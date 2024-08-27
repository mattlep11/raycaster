#pragma once

#ifndef RAYCAST_PLAYER_H
#define RAYCAST_PLAYER_H

#include "./Shared.h"
#include "./Grid.h"

class Grid; // forward declaration to avoid circular dependency errrors
class Player
{
    Vector2D pos{ VIEW_START_X + VIEW_WIDTH * 0.5f, VIEW_START_Y + VIEW_HEIGHT * 0.5f };
    Vector2D dir{ 0.0f, -1.0f };
    float radius{ CELL_WIDTH / 2.0f };

    // updates the position of the player based on current user inputs
    void UpdatePosition(float vx, float vy);
    // updates the rotation of the player based on current user inputs
    void UpdateRotation(float av);
    // resolves any found collision with grid tiles
    void ResolveCollision(const Vector2D& wall);

public:
    Player() = default;
    ~Player() = default;
    // updates the player with new user input
    void Update(const Grid& grid, float vx, float vy, float av);

    const Vector2D GetPos() const { return this->pos; }
    const Vector2D GetDir() const { return this->dir; }
    float GetRadius() const { return this->radius; }
};

#endif