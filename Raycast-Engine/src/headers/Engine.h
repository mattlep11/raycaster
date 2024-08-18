#pragma once

#ifndef RAYCAST_ENGINE_H
#define RAYCAST_ENGINE_H

#include "./Shared.h"
#include "./Map.h"

class Engine
{
    Map tileGrid{};

public:
    // starts the application
    void Run();
    // checks all necessary components for updates
    void PollUpdates();
    // draws the scene details like the borders, fps counter, etc
    void DrawSceneDetails() const;
    // draws the grid lines onto the map viewport
    void DrawMapLines() const;
    // draws a field around the cell the mouse is currently in
    void DrawMouseCell() const;
};

#endif RAYCAST_ENGINE_H