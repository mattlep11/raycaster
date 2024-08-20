#pragma once

#ifndef RAYCAST_GRID_H
#define RAYCAST_GRID_H

#include "./Shared.h"
#include "./Coordinate.h"

class Grid
{
    Coordinate mouseCell{};

public:
    // updates which cell the mouse is currently in
    void UpdateMouseCell();
    const Coordinate GetMouseCell() const { return this->mouseCell; }
};

#endif