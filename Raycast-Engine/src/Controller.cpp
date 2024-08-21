#include "./headers/Controller.h"

void Controller::PollForClicks(Grid& tileGrid)
{
    int mx{ GetMouseX() };
    int my{ GetMouseY() };
    if (IsMouseButtonDown(0))
    {
        // mouse is in the grid
        if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) == mx && clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) == my)
        {
            tileGrid.PlaceTile();
        }

        // TODO: check if the mouse is clicking the SWAP button to change to the 3D perspective
    }
    if (IsMouseButtonDown(1))
    {
        // mouse is in the grid
        if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) == mx && clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) == my)
        {
            tileGrid.RemoveTile();
        }
    }
}

void Controller::PollForKeyEvents()
{
    // TODO: listen for player movement events using WASD
    // TODO: listen for player rotation events using <- and ->
    // TODO: listen for tile selection swapping using Q and E to cycle through options
}