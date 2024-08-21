#pragma once

#ifndef RAYCAST_GRID_H
#define RAYCAST_GRID_H

#include "./Shared.h"
#include "./Tile.h"

class Grid
{
    Tile mouseCell{};
    std::vector<Tile> chunks[NB_CHUNKS]{};
    size_t chunkWidth{};
    size_t chunkHeight{};
    size_t chunksPerRow{};


public:
    Grid();
    ~Grid() = default;

    // updates which cell the mouse is currently in
    void UpdateMouseCell();
    // places a tile at the current mouse cell
    void PlaceTile(TileType type);
    // removes a tile from the current mouse cell
    void RemoveTile();
    // converts a coordinate into the corresponding integer chunk index
    size_t CellToChunk(const Tile& coord) const;

    const Tile GetMouseCell() const { return this->mouseCell; }
    const std::vector<Tile>* GetChunks() const { return this->chunks; }
};

#endif