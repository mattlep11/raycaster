#pragma once

#ifndef RAYCAST_COORD_H
#define RAYCAST_COORD_H

#include "./Shared.h"

// enum used to represent the different tile types, which have different colours or appearances
enum class TileType {
    DEFAULTB,
    DEFAULTG,
    DEFAULTP,
    COUNT = 3
};

struct Tile
{
private:
    int x{};
    int y{};

    TileType type{ TileType::DEFAULTB };

public:
    Tile() = default;
    Tile(int x, int y) : x(x), y(y) {}
    Tile(const Tile& other, TileType type) : x(other.x), y(other.y), type(type) {}
    ~Tile() = default;

    // converts the tile's x and y coordinates into proper screen dimensions
    Vector2D ToVector() const
    {
        return { static_cast<float>(x) * CELL_WIDTH + VIEW_START_X, static_cast<float>(y) * CELL_WIDTH + VIEW_START_Y };
    }

    int GetX() const { return this->x; }
    int GetY() const { return this->y; }
    TileType GetType() const { return this->type; }
    void SetX(int newX) { this->x = newX; }
    void SetY(int newY) { this->y = newY; }
    void SetTileType(TileType newType) { this->type = newType; }

    bool operator==(const Tile& other) const { return this->x == other.x && this->y == other.y; }
    bool operator!=(const Tile& other) const { return this->x != other.x || this->y != other.y; }
};

#endif