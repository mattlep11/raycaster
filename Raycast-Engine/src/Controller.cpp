#include "./headers/Controller.h"

void Controller::PollForClicks()
{
    int mx{ GetMouseX() };
    int my{ GetMouseY() };
    if (IsMouseButtonPressed(0))
    {
        // mouse is in the grid
        if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) == mx && clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) == my)
        {
            // handle adding new structures onto the map
        }

        // TODO: check if the mouse is clicking the SWAP button to change to the 3D perspective
    }
}

void Controller::PollForKeyEvents()
{
    // TODO: listen for player movement events using WASD
    // TODO: listen for player rotation events using <- and ->
    // TODO: listen for tile selection swapping using Q and E to cycle through options
}