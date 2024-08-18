#include "./headers/Engine.h"

void Engine::Run()
{
    SetTargetFPS(TARGET_FPS);
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "RAYCASTER ENGINE o7");

    while (!WindowShouldClose())
    {
        PollUpdates();

        BeginDrawing();

        ClearBackground(BLACK);

        DrawMapLines();
        DrawMouseCell();
        DrawSceneDetails();

        EndDrawing();
    }
}

void Engine::PollUpdates()
{
    tileGrid.UpdateMouseCell();
}

void Engine::DrawSceneDetails() const
{
    DrawRectangleLinesEx(VIEWPORT, 2, WHITE);
    DrawFPS(MENU_START_X, VIEW_START_Y + 50);
}

void Engine::DrawMapLines() const
{
    // horizontals
    const int endX{ VIEW_START_X + VIEW_WIDTH };
    for (int i{ 1 }; i < NB_ROWS; i++)
    {
        int horizontal{ VIEW_START_Y + i * CELL_WIDTH };
        DrawLine(VIEW_START_X, horizontal, endX, horizontal, DARKGRAY);
    }

    // verticals
    const int endY{ VIEW_START_Y + VIEW_HEIGHT };
    for (int i{ 1 }; i < NB_COLS; i++)
    {
        int vertical{ VIEW_START_X + i * CELL_WIDTH };
        DrawLine(vertical, VIEW_START_Y, vertical, endY, DARKGRAY);
    }
}

void Engine::DrawMouseCell() const
{
    int mx{ tileGrid.GetMouseCell().GetX() };
    int my{ tileGrid.GetMouseCell().GetY() };

    // -1 indicates a mouse position outside the grid
    if (mx == -1 || my == -1)
        return;
    DrawRectangleLines(mx * CELL_WIDTH + VIEW_START_X, my * CELL_WIDTH + VIEW_START_Y, CELL_WIDTH, CELL_WIDTH, YELLOW);
}