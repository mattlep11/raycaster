#pragma once

#ifndef RAYCAST_ENGINE_H
#define RAYCAST_ENGINE_H

#include "./Shared.h"

class Engine
{
public:
    // starts the application
    void Run();
    // draws the scene details like the borders, fps counter, etc
    void DrawSceneDetails() const;
};

#endif RAYCAST_ENGINE_H