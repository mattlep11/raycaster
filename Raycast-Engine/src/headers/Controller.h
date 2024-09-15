#pragma once

#ifndef RAYCAST_CONTROLLER_H
#define RAYCAST_CONTROLLER_H

#include "./Shared.h"
#include "./Grid.h"

class Controller
{
    // array of possible colours which will be injected into the grid cells to denote what they should be painted
    static constexpr int NB_COLOURS{ 3 };
    static constexpr Color colours[NB_COLOURS]{ DARKBLUE, DARKGREEN, DARKPURPLE };

    int selectedTileColour{};

    // states
    bool renderViewMarkers{ false };

public:
    Controller() = default;
    ~Controller() = default;

    // listens for clicks and delegates the click event to the relevant component
    void HandleClickEvents(Grid& tileGrid) const;
    // listens for key presses and delegates the key event to the relevant component
    void HandleKeyEvents(const Grid& tileGrid, Player& player);

    Color GetColour(int type) const { return this->colours[type]; }
    int GetSelectedTile() const { return this->selectedTileColour; }

    bool ShouldRenderViewMarkers() const { return this->renderViewMarkers; }
};

#endif