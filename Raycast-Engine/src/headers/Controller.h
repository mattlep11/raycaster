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
    bool render3D{ false };

public:
    Controller() = default;
    ~Controller() = default;

    // listens for clicks and delegates the click event to the relevant component
    void HandleClickEvents(Grid& tileGrid);
    // listens for key presses and delegates the key event to the relevant component
    void HandleKeyEvents();
    // listens for movement key presses and uses them to update the connected player's position
    void HandleMovementEvents(const Grid& tileGrid, Player& player) const;

    Color GetColour(int type) const { return this->colours[type]; }
    int GetSelectedTile() const { return this->selectedTileColour; }

    bool ShouldRenderViewMarkers() const { return this->renderViewMarkers; }
    bool ShouldRender3D() const { return this->render3D; }
};

#endif