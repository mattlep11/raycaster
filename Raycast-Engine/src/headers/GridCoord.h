#pragma once

#ifndef RAYCAST_COORD_H
#define RAYCAST_COORD_H

#include "./Shared.h"

struct GridCoord
{
private:
    int row{};
    int col{};

public:
    GridCoord() = default;
    GridCoord(int row, int col) : row(row), col(col) {}
    GridCoord(const GridCoord& other) : row(other.row), col(other.col) {}
    ~GridCoord() = default;

    // converts the tile's x and y coordinates into proper screen dimensions
    Vector2D ToVector() const
    {
        return { static_cast<float>(row) * CELL_WIDTH + VIEW_START_X, static_cast<float>(col) * CELL_WIDTH + VIEW_START_Y };
    }

    int GetRow() const { return this->row; }
    int GetCol() const { return this->col; }
    void SetRow(int newRow) { this->row = newRow; }
    void SetCol(int newCol) { this->col = newCol; }

    bool operator==(const GridCoord& other) const { return this->row == other.row && this->col == other.col; }
    bool operator!=(const GridCoord& other) const { return this->row != other.row || this->col != other.col; }
};

#endif