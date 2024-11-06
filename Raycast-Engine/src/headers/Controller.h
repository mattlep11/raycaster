#pragma once

#ifndef RAYCAST_CONTROLLER_H
#define RAYCAST_CONTROLLER_H

#include "./Shared.h"
#include "./Grid.h"

class Controller
{
    // array of possible colours which will be injected into the grid cells to denote what they should be painted
    static constexpr int NB_UNIQUE_TILES{ 3 };
    static constexpr Color colours[]{ DARKBLUE, DARKGREEN, DARKPURPLE, BLUE, GREEN, PURPLE, GRAY, LIGHTGRAY };

    int selectedTileColour{};

    // states
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

    // returns the requested colours, alt flag can be used to get a lighter alternate version
    Color GetColour(int type, bool alt) const;
    int GetSelectedTile() const { return this->selectedTileColour; }

    bool ShouldRender3D() const { return this->render3D; }
};

#endif