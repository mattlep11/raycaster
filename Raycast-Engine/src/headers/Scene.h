#pragma once

#ifndef RAYCAST_SCENE_H
#define RAYCAST_SCENE_H

#include "./Shared.h"
#include "./Controller.h"

class Scene
{
    Controller app{};
    Grid tileGrid{};

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

    // draws a field around the cell the mouse is currently in
    void DrawMouseCell() const;

public:
    // starts the application
    void Run();
};

#endif RAYCAST_ENGINE_H