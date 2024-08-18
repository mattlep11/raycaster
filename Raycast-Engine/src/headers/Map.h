#pragma once

#ifndef RAYCAST_MAP_H
#define RAYCAST_MAP_H

#include "./Shared.h"
#include "./Coordinate.h"

class Map
{
    Coordinate mouseCell{};

public:
    // updates which cell the mouse is currently in
    void UpdateMouseCell();
    const Coordinate GetMouseCell() const { return this->mouseCell; }
};

#endif