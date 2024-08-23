#pragma once

#ifndef RAYCAST_PLAYER_H
#define RAYCAST_PLAYER_H

#include "./Shared.h"

class Player
{
    Vector2D pos{ VIEW_START_X + VIEW_WIDTH * 0.5f, VIEW_START_Y + VIEW_HEIGHT * 0.5f };
    Vector2D dir{ 0.0f, -1.0f };
    float radius{ CELL_WIDTH / 2.0f };

    // updates the position of the player based on current user inputs
    void UpdatePosition(float vx, float vy);
    // updates the rotation of the player based on current user inputs
    void UpdateRotation(float av);

public:
    Player() = default;
    ~Player() = default;
    // updates the player with new user input
    void Update(float vx, float vy, float av);

    const Vector2D GetPos() const { return this->pos; }
    const Vector2D GetDir() const { return this->dir; }
    float GetRadius() const { return this->radius; }
};

#endif