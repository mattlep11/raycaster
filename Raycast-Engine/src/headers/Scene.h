#pragma once

#ifndef RAYCAST_SCENE_H
#define RAYCAST_SCENE_H

#include "./Shared.h"
#include "./Controller.h"

class Scene
{
    Controller app{};
    Player plr;
    Grid tileGrid{ plr };

    // checks all necessary components for updates
    void PollUpdates();
    // draws the scene details like the borders, fps counter, etc
    void DrawSceneDetails() const;
    // draws the large swap button to the screen
    void DrawSwapButton() const;
    // draws the tile selector display to the screen
    void DrawTileSelector() const;
    // draws the grid lines onto the map viewport
    void DrawGridLines() const;
    // draws the grid tiles onto the map viewport
    void DrawGridTiles() const;
    // draws the 2D player onto the map viewport
    void DrawPlayer(const Player& player) const;
    // draws the player's rays
    void DrawPlayerViewRays(const Player& player) const;
    // draws the vertical strips that make up the 3D wall tiles
    void Draw3DWalls(const Player& player) const;
    // draws a field around the cell the mouse is currently in
    void DrawMouseCell() const;

public:
    Scene() = default;
    ~Scene() = default;

    // starts the application
    void Run();
};

#endif RAYCAST_ENGINE_H