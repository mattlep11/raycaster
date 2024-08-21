#pragma once

#ifndef RAYCAST_GRID_H
#define RAYCAST_GRID_H

#include "./Shared.h"
#include "./Coordinate.h"

class Grid
{
    Coordinate mouseCell{};
    std::vector<Coordinate> chunks[NB_CHUNKS]{};
    size_t chunkWidth{};
    size_t chunkHeight{};
    size_t chunksPerRow{};


public:
    Grid();
    ~Grid() = default;

    // updates which cell the mouse is currently in
    void UpdateMouseCell();
    // places a tile at the current mouse cell
    void PlaceTile();
    // removes a tile from the current mouse cell
    void RemoveTile();
    // converts a coordinate into the corresponding integer chunk index
    size_t CellToChunk(const Coordinate& coord) const;

    const Coordinate GetMouseCell() const { return this->mouseCell; }
    const std::vector<Coordinate>* GetChunks() const { return this->chunks; }
};

#endif