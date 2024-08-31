#include "./headers/Controller.h"

void Controller::HandleClickEvents(Grid& tileGrid) const
{
    int mx{ GetMouseX() };
    int my{ GetMouseY() };
    if (IsMouseButtonDown(0))
    {
        // mouse is in the grid
        if (clamp<int>(mx, VIEW_START_X, VIEW_END_X - 1) == mx && clamp<int>(my, VIEW_START_Y, VIEW_END_Y - 1) == my)
            tileGrid.PlaceTile(selectedTile);

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
        selectedTile = static_cast<TileType>((static_cast<int>(selectedTile) + 1) % static_cast<int>(TileType::COUNT));
    else if (IsKeyPressed(KEY_Q))
        selectedTile = static_cast<TileType>((static_cast<int>(selectedTile) - 1 + static_cast<int>(TileType::COUNT)) % static_cast<int>(TileType::COUNT));

    // key modifiable states
    if (IsKeyPressed(KEY_GRAVE))
        renderViewMarkers = !renderViewMarkers;

    // comptuting final velocities per update to update the player with
    float vx{};
    float vy{};
    float av{};
    if (IsKeyDown(KEY_W))
        vy -= PLR_SPEED;
    if (IsKeyDown(KEY_S))
        vy += PLR_SPEED;
    if (IsKeyDown(KEY_A))
        vx -= PLR_SPEED;
    if (IsKeyDown(KEY_D))
        vx += PLR_SPEED;
    if (IsKeyDown(KEY_RIGHT))
        av += PLR_R_SPEED;
    if (IsKeyDown(KEY_LEFT))
        av -= PLR_R_SPEED;

    player.Update(tileGrid, vx, vy, av);
}