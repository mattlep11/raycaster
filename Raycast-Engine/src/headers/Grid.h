#pragma once

#ifndef RAYCAST_GRID_H
#define RAYCAST_GRID_H

#include "./Shared.h"
#include "./GridCoord.h"
#include "./Player.h"

class Player; // forward declaration to avoid circular dependency errors
class Grid
{
    GridCoord mouseCell{};
    Player& player;

    int grid[NB_ROWS][NB_COLS]{};

public:
    Grid(Player& player);
    ~Grid() = default;

    // returns the value (wall-type) stored at the grid coordinates (row, col)
    int Get(int row, int col) const;
    // updates which cell the mouse is currently in
    void UpdateMouseCell();
    // places a tile at the current mouse cell
    void PlaceTile(int type);
    // removes a tile from the current mouse cell
    void RemoveTile();
    // converts a vector of real coordinates into a set of grid coordinates
    GridCoord VectorToCoord(const Vector2D& v) const;
    const GridCoord GetMouseCell() const { return this->mouseCell; }
    Player& GetPlayer() { return player; } // returns player reference
};

#endif