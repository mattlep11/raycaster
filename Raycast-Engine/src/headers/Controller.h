#pragma once

#ifndef RAYCAST_CONTROLLER_H
#define RAYCAST_CONTROLLER_H

#include "./Shared.h"
#include "./Grid.h"

class Controller
{
    // array of possible colours mapped 1:1 with the TileType enum in Tile.h
    const Color colours[static_cast<int>(TileType::COUNT)]{ DARKBLUE, DARKGREEN, DARKPURPLE };
    TileType selectedTile{ TileType::DEFAULTB };

    // states
    bool renderViewMarkers{ false };

public:
    Controller() = default;
    ~Controller() = default;

    // listens for clicks and delegates the click event to the relevant component
    void HandleClickEvents(Grid& tileGrid) const;
    // listens for key presses and delegates the key event to the relevant component
    void HandleKeyEvents(const Grid& tileGrid, Player& player);

    Color GetColour(TileType type) const { return this->colours[static_cast<int>(type)]; }
    TileType GetSelectedTile() const { return this->selectedTile; }

    bool ShouldRenderViewMarkers() const { return this->renderViewMarkers; }
};

#endif