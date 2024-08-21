#pragma once

#ifndef RAYCAST_COORD_H
#define RAYCAST_COORD_H

#include "./Shared.h"

struct Coordinate
{
private:
    int x{};
    int y{};

public:
    Coordinate() = default;
    Coordinate(int x, int y) : x(x), y(y) {}
    Coordinate(const Coordinate& other) : x(other.x), y(other.y) {}
    ~Coordinate() = default;

    int GetX() const { return this->x; }
    int GetY() const { return this->y; }
    void SetX(int newX) { this->x = newX; }
    void SetY(int newY) { this->y = newY; }

    bool operator==(const Coordinate& other) const { return this->x == other.x && this->y == other.y; }
    bool operator!=(const Coordinate& other) const { return this->x != other.x || this->y != other.y; }
};

#endif