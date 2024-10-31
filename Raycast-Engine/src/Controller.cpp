#include "./headers/Controller.h"

void Controller::HandleClickEvents(Grid& tileGrid) const
{
    int mx{ GetMouseX() };
    int my{ GetMouseY() };
    if (IsMouseButtonDown(0))
    {
        // mouse is in the grid
        if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) == mx && clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) == my)
            tileGrid.PlaceTile(selectedTileColour);

        // TODO: check if the mouse is clicking the SWAP button to change to the 3D perspective
    }
    if (IsMouseButtonDown(1))
    {
        // mouse is in the grid
        if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) == mx && clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) == my)
            tileGrid.RemoveTile();
    }
}

void Controller::HandleKeyEvents(const Grid& tileGrid, Player& player)
{
    // cycle through the tile types in forward/reverse direction
    if (IsKeyPressed(KEY_E))
        selectedTileColour = ++selectedTileColour % NB_COLOURS;
    else if (IsKeyPressed(KEY_Q))
        selectedTileColour = (--selectedTileColour + NB_COLOURS) % NB_COLOURS;

    // key modifiable states
    if (IsKeyPressed(KEY_Z))
        renderViewMarkers = !renderViewMarkers;

    // comptuting final velocities per update to update the player with
    float v{};
    float vStrafe{};
    float av{};
    if (IsKeyDown(KEY_W))
        v += PLR_SPEED;
    if (IsKeyDown(KEY_S))
        v -= PLR_SPEED;
    if (IsKeyDown(KEY_A))
        vStrafe -= PLR_SPEED;
    if (IsKeyDown(KEY_D))
        vStrafe += PLR_SPEED;
    if (IsKeyDown(KEY_RIGHT))
        av += PLR_R_SPEED;
    if (IsKeyDown(KEY_LEFT))
        av -= PLR_R_SPEED;

    player.Update(tileGrid, v, vStrafe, av);
}