#include "./headers/Engine.h"

void Engine::Run()
{
    SetTargetFPS(TARGET_FPS);
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "RAYCASTER ENGINE o7");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawSceneDetails();

        EndDrawing();
    }
}

void Engine::DrawSceneDetails() const
{
    DrawRectangleLinesEx(VIEWPORT, 2, WHITE);
    DrawFPS(MENU_START_X, VIEW_START_Y + 50);
}