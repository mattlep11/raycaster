#include "./headers/Controller.h"

Color Controller::GetColour(int type, bool alt) const
{
    if (type < 0 || type >= NB_UNIQUE_TILES)
        return (alt) ? colours[NB_UNIQUE_TILES * 2 + 1] : colours[NB_UNIQUE_TILES * 2];
    else
        return (alt) ? colours[type + NB_UNIQUE_TILES] : colours[type];
}

void Controller::HandleClickEvents(Grid& tileGrid)
{
    int mx{ GetMouseX() };
    int my{ GetMouseY() };
    if (IsMouseButtonDown(0))
    {
        // mouse is in the grid
        if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) == mx && clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) == my)
            tileGrid.PlaceTile(selectedTileColour);
    }

    // separate if statement to only check for a single mouse press (will avoid represses multiple times per click)
    if (IsMouseButtonPressed(0))
    {
        // mouse is over the swap button
        if (clamp<int>(mx, SWAP_BTN_START_X, SWAP_BTN_START_X + SWAP_BTN_WIDTH) == mx
            && clamp<int>(my, SWAP_BTN_START_Y, SWAP_BTN_START_Y + SWAP_BTN_HEIGHT) == my)
        {
            render3D = !render3D;
        }
    }

    if (IsMouseButtonDown(1))
    {
        // mouse is in the grid
        if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) == mx && clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) == my)
            tileGrid.RemoveTile();
    }
}

void Controller::HandleKeyEvents()
{
    // cycle through the tile types in forward/reverse direction
    if (IsKeyPressed(KEY_E))
        selectedTileColour = ++selectedTileColour % NB_UNIQUE_TILES;
    else if (IsKeyPressed(KEY_Q))
        selectedTileColour = (--selectedTileColour + NB_UNIQUE_TILES) % NB_UNIQUE_TILES;

    // key modifiable states
    if (IsKeyPressed(KEY_Z))
        renderViewMarkers = !renderViewMarkers;
}

void Controller::HandleMovementEvents(const Grid& tileGrid, Player& player) const
{
    // comptuting final velocities per update to update the player with
    float v{};
    float vAlt{};
    float av{};

    if (IsKeyDown(KEY_W))
        v += PLR_SPEED;
    if (IsKeyDown(KEY_S))
        v -= PLR_SPEED;

    // flip vertical velocity for 2D pov to maintain cardinal movement
    if (!render3D)
        v = -v;

    if (IsKeyDown(KEY_A))
        vAlt -= PLR_SPEED;
    if (IsKeyDown(KEY_D))
        vAlt += PLR_SPEED;

    // player rotation
    if (IsKeyDown(KEY_RIGHT))
        av += PLR_R_SPEED;
    if (IsKeyDown(KEY_LEFT))
        av -= PLR_R_SPEED;

    player.Update(tileGrid, v, vAlt, av, render3D);
}