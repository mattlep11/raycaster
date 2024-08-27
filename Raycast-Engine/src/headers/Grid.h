#pragma once

#ifndef RAYCAST_GRID_H
#define RAYCAST_GRID_H

#include "./Shared.h"
#include "./Tile.h"
#include "./Player.h"

class Player; // forward declaration to avoid circular dependency errors
class Grid
{
    Tile mouseCell{};
    Player& player;

    std::vector<Tile> chunks[NB_CHUNKS]{};
    size_t chunkWidth{};
    size_t chunkHeight{};
    size_t chunksPerRow{};

public:
    Grid(Player& player);
    ~Grid() = default;

    // updates which cell the mouse is currently in
    void UpdateMouseCell();
    // places a tile at the current mouse cell
    void PlaceTile(TileType type);
    // removes a tile from the current mouse cell
    void RemoveTile();
    // converts a coordinate into the corresponding integer chunk index
    size_t CellToChunk(const Tile& coord) const;
    // converts a vector into the corresponding integer chunk index
    size_t VectorToChunk(const Vector2D& vec) const;

    const Tile GetMouseCell() const { return this->mouseCell; }
    const std::vector<Tile>* GetChunks() const { return this->chunks; }
    Player& GetPlayer() { return player; } // returns player reference
};

#endif